#include <bit>

#include "ManagedObject.hpp"
#include "NativeObject.hpp"

#include "Method.hpp"

namespace REFrameworkNET {
REFrameworkNET::InvokeRet^ Method::Invoke(System::Object^ obj, array<System::Object^>^ args) {
    // We need to convert the managed objects to 8 byte representations
    std::vector<void*> args2{};
    args2.resize(args->Length);

    for (int i = 0; i < args->Length; ++i) try {
        if (args[i] == nullptr) {
            args2[i] = nullptr;
            continue;
        }

        //args2[i] = args[i]->ptr();
        const auto t = args[i]->GetType();

        if (t == REFrameworkNET::ManagedObject::typeid) {
            args2[i] = safe_cast<REFrameworkNET::ManagedObject^>(args[i])->Ptr();
        } else if (t == System::Boolean::typeid) {
            bool v = System::Convert::ToBoolean(args[i]);
            args2[i] = (void*)(intptr_t)v;
        } else if (t == System::Int32::typeid) {
            int32_t v = System::Convert::ToInt32(args[i]);
            args2[i] = (void*)(intptr_t)v;
        } else if (t == System::Byte::typeid) {
            uint8_t v = System::Convert::ToByte(args[i]);
            args2[i] = (void*)(uint64_t)v;
        } else if (t == System::UInt16::typeid) {
            uint16_t v = System::Convert::ToUInt16(args[i]);
            args2[i] = (void*)(uint64_t)v;
        } else if (t == System::UInt32::typeid) {
            uint32_t v = System::Convert::ToUInt32(args[i]);
            args2[i] = (void*)(uint64_t)v;
        } else if (t == System::Single::typeid) {
            // this might seem counterintuitive, converting a float to a double
            // but the invoke wrappers ALWAYS expect a double, so we need to do this
            // even when they take a System.Single, the wrappers take in a double and convert it to a float
            float v = System::Convert::ToSingle(args[i]);
            auto d = (double)v;
            auto n = *(int64_t*)&d;
            args2[i] = (void*)(uint64_t)n;
        } else if (t == System::UInt64::typeid) {
            uint64_t v = System::Convert::ToUInt64(args[i]);
            args2[i] = (void*)(uint64_t)v;
        } else if (t == System::Double::typeid) {
            double v = System::Convert::ToDouble(args[i]);
            auto n = *(int64_t*)&v;
            args2[i] = (void*)(uint64_t)n;
        } else if (t == System::IntPtr::typeid) {
            args2[i] = (void*)(uint64_t)System::Convert::ToInt64(args[i]);
        } else {
            args2[i] = nullptr;
            System::Console::WriteLine("Unknown type passed to method invocation @ arg " + i);
        }
    } catch (System::Exception^ e) {
        System::Console::WriteLine("Error converting argument " + i + ": " + e->Message);
    }

    void* obj_ptr = nullptr;

    if (obj != nullptr) try {
        const auto obj_t = obj->GetType();

        if (obj_t == System::IntPtr::typeid) {
            obj_ptr = (void*)(intptr_t)safe_cast<System::IntPtr>(obj).ToPointer();
        } else if (obj_t == System::UIntPtr::typeid) {
            obj_ptr = (void*)(uintptr_t)safe_cast<System::UIntPtr>(obj).ToUInt64();
        } else if (obj_t == REFrameworkNET::ManagedObject::typeid) {
            obj_ptr = safe_cast<REFrameworkNET::ManagedObject^>(obj)->Ptr();
        } else if (obj_t == REFrameworkNET::NativeObject::typeid) {
            obj_ptr = safe_cast<REFrameworkNET::NativeObject^>(obj)->Ptr();
        } else {
            System::Console::WriteLine("Unknown type passed to method invocation @ obj");
        }
    } catch (System::Exception^ e) {
        System::Console::WriteLine("Error converting object: " + e->Message);
    }

    const auto native_result = m_method->invoke((reframework::API::ManagedObject*)obj_ptr, args2);

    return gcnew REFrameworkNET::InvokeRet(native_result);
}
}