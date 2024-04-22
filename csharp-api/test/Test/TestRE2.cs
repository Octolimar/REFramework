using System;
using System.Collections;
using System.Collections.Generic;
using System.Dynamic;
using System.Reflection;
using System.Threading;
using app.ropeway;
using ImGuiNET;
using REFrameworkNET;
using REFrameworkNET.Callbacks;

public class TestRE2Plugin {
    static bool IsRunningRE2 => Environment.ProcessPath.Contains("re2", StringComparison.CurrentCultureIgnoreCase);

    [REFrameworkNET.Attributes.PluginEntryPoint]
    public static void Main() {
        if (IsRunningRE2) {
            Console.WriteLine("Running in RE2");
        } else {
            Console.WriteLine("Not running in RE2");
            return;
        }

        RE2HookBenchmark.InstallHook();

        ImGuiRender.Pre += () => {
            if (ImGui.Begin("Test Window")) {
                ImGui.Text("RE2");
                ImGui.Separator();

                System.Collections.Generic.List<long> threadRanks = new();

                foreach(var tdata in RE2HookBenchmark.threadData) {
                    threadRanks.Add(tdata.Value.threadID);
                }

                // Sort by highest running average
                threadRanks.Sort((a, b) => {
                    var aData = RE2HookBenchmark.threadData[a];
                    var bData = RE2HookBenchmark.threadData[b];
                    return aData.runningAvg.CompareTo(bData.runningAvg);
                });

                var totalThreadRanks = threadRanks.Count;

                foreach(var tdata in RE2HookBenchmark.threadData) {
                    var rank = threadRanks.IndexOf(tdata.Value.threadID) + 1;
                    var greenColor = 1.0f - (float)rank / (float)totalThreadRanks;
                    var redColor = (float)rank / (float)totalThreadRanks;

                    //ImGui.Text("Thread ID: " + tdata.Value.threadID + " Avg: " + tdata.Value.runningAvg.ToString("0.000") + " µs");
                    ImGui.PushStyleColor(ImGuiCol.Text, new System.Numerics.Vector4(redColor, greenColor, 0f, 1.0f));
                    ImGui.PlotLines("Thread " + tdata.Value.threadID, ref tdata.Value.benchmarkData[0], 1000, tdata.Value.callCount % 1000, tdata.Value.runningAvg.ToString("0.000") + " µs", 0, (float)tdata.Value.runningAvg * 2.0f, new System.Numerics.Vector2(0, 30));
                    ImGui.PopStyleColor();
                }

                ImGui.PushStyleColor(ImGuiCol.Text, new System.Numerics.Vector4(0.5f, 1f, 0.4f, 1.0f));
                ImGui.PlotLines("Overall Benchmark", ref RE2HookBenchmark.BenchmarkData[0], 1000, RE2HookBenchmark.MeasureCount % 1000, RE2HookBenchmark.RunningAvg.ToString("0.000") + " µs", 0, (float)RE2HookBenchmark.RunningAvg * 2.0f, new System.Numerics.Vector2(0, 40));
                ImGui.PopStyleColor();
                
                if (ImGui.TreeNode("Player")) {
                    var playerManager = API.GetManagedSingletonT<app.ropeway.PlayerManager>();
                    var player = playerManager.get_CurrentPlayer();
                    if (player != null) {
                        ImGui.Text("Player is not null");
                    } else {
                        ImGui.Text("Player is null");
                    }
                    ImGui.TreePop();
                }

                ImGui.End();
            }
        };

        // Benchmarking the effects of threading on invoking game code
        for (int i = 0; i < 2; ++i) {
            threads.Add(new System.Threading.Thread(() => {
                /*while (!cts.Token.IsCancellationRequested) {
                    RE2HookBenchmark.Bench(BenchFnAction);
                    // We must manually call the GC in our own threads not owned by the game
                    API.LocalFrameGC();
                }*/

                API.LocalFrameGC();
            }));
        }

        foreach (var thread in threads) {
            thread.Start();
        }
    }

    [REFrameworkNET.Attributes.PluginExitPoint]
    public static void Unload() {
        cts.Cancel();
        foreach (var thread in threads) {
            thread.Join();
        }
    }

    static System.Threading.ReaderWriterLockSlim rwl = new();
    static System.Collections.Concurrent.ConcurrentDictionary<long, bool> test = new(Environment.ProcessorCount * 2, 8192);
    public static void BenchFn() {
        var playerManager = API.GetManagedSingletonT<app.ropeway.PlayerManager>();
        var player = playerManager.get_CurrentPlayer();
        if (player != null) {
            via.Component playerControllerRaw = player.getComponent(app.Collision.HitController.REFType.GetRuntimeType().As<_System.Type>());
            if (playerControllerRaw != null) {
                var playerController = (playerControllerRaw as IObject).As<app.Collision.HitController>();
                for (int i = 0; i < 1; ++i) {
                    //rwl.EnterReadLock();
                    //rwl.ExitReadLock();
                    //playerController.
                    //playerController.get_DeltaTime();
                    var gameobj = playerController.get_GameObject();

                    if (gameobj != null) {
                        /*var backToPlayerController = gameobj.getComponent(app.Collision.HitController.REFType.GetRuntimeType().As<_System.Type>());

                        if (backToPlayerController != null) {
                            //System.Console.WriteLine("Back to player controller!!!");
                        }*/
                    }
                    //get_GameObjectFn.Invoke(playerController, null);
                    //object result = null;
                    //get_GameObjectFn.HandleInvokeMember_Internal(playerController, null, ref result);
                }

                var refCount = ((playerController.get_GameObject() as IProxy).GetInstance() as ManagedObject).GetReferenceCount();
                System.Console.WriteLine("PlayerController ref count: " + refCount);
            }
        }
    }

    public static System.Action BenchFnAction = BenchFn;

    static Method get_GameObjectFn = via.Component.REFType.GetMethod("get_GameObject");

    static List<System.Threading.Thread> threads = new();

    static System.Threading.CancellationTokenSource cts = new();
}

public class RE2HookBenchmark {
    public static int MeasureCount { get; private set; }
    static int callCount = 0;
    static double totalMicros = 0.0;
    public static double RunningAvg { get; private set; }

    public static double HighestMicros { get; private set; } = 0.0;
    public static float[] BenchmarkData { get; private set; } = new float[1000];
    
    static System.Threading.ReaderWriterLockSlim rwl = new();

    internal class ThreadData {
        internal long threadID;
        internal double totalMicros;
        internal int callCount;
        internal double highestMicros;
        internal double runningAvg;
        internal float[] benchmarkData = new float[1000];
    };

    internal static System.Collections.Concurrent.ConcurrentDictionary<long, ThreadData> threadData = new(Environment.ProcessorCount * 2, 8192);

    public static void Bench(System.Action action) {
        var threadID = System.Threading.Thread.CurrentThread.ManagedThreadId;
        ThreadData? data = null;
        if (!threadData.ContainsKey(threadID)) {
            data = new ThreadData() { threadID = threadID };
            threadData.TryAdd(threadID, data);
        } else {
            threadData.TryGetValue(threadID, out data);
        }

        var sw = _System.Diagnostics.Stopwatch.REFType.CreateInstance(0).As<_System.Diagnostics.Stopwatch>();
        //var sw2 = new System.Diagnostics.Stopwatch();
        sw.Start();

        action();

        sw.Stop();
        var elapsedTicks = (double)sw.get_ElapsedTicks();
        var elapsedMicros = elapsedTicks / (double)TimeSpan.TicksPerMicrosecond;

        data.totalMicros += elapsedMicros;
        data.callCount++;

        if (elapsedMicros > data.highestMicros) {
            data.highestMicros = elapsedMicros;
        }
        
        data.runningAvg = data.totalMicros / (double)data.callCount;
        data.benchmarkData[data.callCount % 1000] = (float)elapsedMicros;

        if (data.callCount >= 1000) {
            data.callCount = 0;
            data.totalMicros = 0.0;
        }

        rwl.EnterWriteLock();

        callCount++;

        if (callCount >= 5) {
            totalMicros += elapsedMicros;
            MeasureCount++;
            RunningAvg = totalMicros / MeasureCount;
            BenchmarkData[callCount % 1000] = (float)elapsedMicros;

            if (elapsedMicros > HighestMicros) {
                HighestMicros = elapsedMicros;
            }
        }
        
        if (MeasureCount >= 1000) {
            MeasureCount = 0;
            totalMicros = 0.0;
        }

        rwl.ExitWriteLock();
    }

    static PreHookResult Pre(System.Span<ulong> args) {
        var hitController = ManagedObject.ToManagedObject(args[1]).As<app.Collision.HitController>();

        //Bench(TestRE2Plugin.BenchFnAction);
        Bench(() => {
            for (int i = 0; i < 10000; ++i) {
                var gameobj = hitController.get_GameObject();
                if (gameobj != null) {
                }
            }
        });

        return PreHookResult.Continue;
    }

    static void Post(ref ulong retval) {
    }

    public static void InstallHook() {
        app.Collision.HitController.REFType
            .GetMethod("update")
            .AddHook(false)
            .AddPre(Pre)
            .AddPost(Post);
    }
}