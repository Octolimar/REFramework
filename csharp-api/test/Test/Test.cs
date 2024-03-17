// Import REFramework::API

using System;
using System.Reflection;

using System.Text;
using System.IO;

public static class ApiWrapperGenerator
{
    public static void GenerateWrapper(Type type, string outputPath)
    {
        var sb = new StringBuilder();
        sb.AppendLine("using System;");
        sb.AppendFormat("public class {0}Wrapper\n", type.Name);
        sb.AppendLine("{");
        sb.AppendFormat("    private readonly {0} _original;\n\n", type.Name);
        sb.AppendFormat("    public {0}Wrapper({0} original)\n", type.Name);
        sb.AppendLine("    {");
        sb.AppendLine("        _original = original;");
        sb.AppendLine("    }\n");

        foreach (var method in type.GetMethods(BindingFlags.Public | BindingFlags.Instance))
        {
            var pascalCaseName = ConvertToPascalCase(method.Name);
            var parameters = method.GetParameters();

            sb.AppendFormat("    public {0} {1}({2})\n",
                method.ReturnType.Name, pascalCaseName, GetParameterDeclaration(parameters));
            sb.AppendLine("    {");
            sb.AppendFormat("        {0}_original.{1}({2});\n",
                method.ReturnType.Name == "void" ? "" : "return ",
                method.Name,
                GetParameterInvocation(parameters));
            sb.AppendLine("    }\n");
        }

        sb.AppendLine("}");

        File.WriteAllText(outputPath, sb.ToString());
    }

    private static string ConvertToPascalCase(string snakeCaseName)
    {
        // Split the snake_case string into words
        string[] words = snakeCaseName.Split('_');

        // Capitalize the first letter of each word
        for (int i = 0; i < words.Length; i++)
        {
            if (words[i].Length > 0)
            {
                words[i] = char.ToUpper(words[i][0]) + words[i].Substring(1);
            }
        }

        // Join the words to form the PascalCase string
        string pascalCaseName = string.Join("", words);

        return pascalCaseName;
    }

    private static string GetParameterDeclaration(ParameterInfo[] parameters)
    {
        var sb = new StringBuilder();
        for (int i = 0; i < parameters.Length; i++)
        {
            sb.AppendFormat("{0} {1}", parameters[i].ParameterType.Name, parameters[i].Name);
            if (i < parameters.Length - 1)
            {
                sb.Append(", ");
            }
        }
        return sb.ToString();
    }

    private static string GetParameterInvocation(ParameterInfo[] parameters)
    {
        var sb = new StringBuilder();
        for (int i = 0; i < parameters.Length; i++)
        {
            sb.Append(parameters[i].Name);
            if (i < parameters.Length - 1)
            {
                sb.Append(", ");
            }
        }
        return sb.ToString();
    }
}

class REFrameworkPlugin {
    public static void Main(REFrameworkNET.API api_) {
        Console.WriteLine("Testing REFrameworkAPI...");

        // Convert api.Get() type to pass to GenerateWrapper
        var currentDir = Directory.GetCurrentDirectory();
        var targetType = typeof(reframework.API.Method);
        var outputPath = Path.Combine(currentDir, "MethodWrapper.cs");

        ApiWrapperGenerator.GenerateWrapper(targetType, outputPath);

        // Open in explorer
        System.Diagnostics.Process.Start("explorer.exe", currentDir);

        var api = new APIWrapper(api_.Get());
        var tdb = api.GetTDB();

        Console.WriteLine(tdb.GetNumTypes().ToString() + " types");

        /*var typesSorted = new System.Collections.Generic.List<String>();

        for (uint i = 0; i < tdb.GetNumTypes(); i++) {
            var t = tdb.GetType(i);
            if (t == null) {
                continue;
            }

            typesSorted.Add(t.GetFullName());
        }

        typesSorted.Sort();*/

        var singletons = api.GetManagedSingletons();

        foreach (var singletonDesc in singletons) {
            var singleton = new ManagedObjectWrapper(singletonDesc.instance);

            Console.WriteLine(singleton.GetTypeDefinition().GetFullName());

            // Log all methods
            var td = singleton.GetTypeDefinition();
            var methods = td.GetMethods();

            foreach (var method in methods) {
                Console.WriteLine(" " + method.get_name());
            }

            var fields = td.GetFields();

            foreach (var field in fields) {
                Console.WriteLine(" " + field.get_name());
            }
        }

        var sceneManager = api.GetNativeSingleton("via.SceneManager");
        Console.WriteLine("sceneManager: " + sceneManager);
        var sceneManager_t = tdb.FindType("via.SceneManager");
        Console.WriteLine("sceneManager_t: " + sceneManager_t);
        var get_CurrentScene = sceneManager_t.FindMethod("get_CurrentScene");
        Console.WriteLine("get_CurrentScene: " + get_CurrentScene);
        var scene = get_CurrentScene.invoke(sceneManager, new object[]{}).Ptr;

        Console.WriteLine("scene: " + scene);

        if (scene != null) {
            var scene_t = tdb.FindType("via.Scene");
            var set_TimeScale = scene_t.FindMethod("set_TimeScale");

            Console.WriteLine("set_TimeScale: " + set_TimeScale);

            set_TimeScale.invoke(scene, new object[]{ 0.1f });
        }
    }
};