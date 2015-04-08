#include "clover.h"
#include "common.h"

static unsigned int object_size()
{
    unsigned int size;

    size = sizeof(sCLMethodObject);

    /// align to 4 byte boundry
    size = (size + 3) & ~3;

    return size;
}

CLObject create_method_object(CLObject type_object, sCLClass* klass, sCLMethod* method)
{
    unsigned int size;
    CLObject object;

    size = object_size();

    object = alloc_heap_mem(size, type_object);

    CLMETHOD(object)->mClass = klass;
    CLMETHOD(object)->mMethod = method;

    return object;
}

static CLObject create_method_object_for_new(CLObject type_object, sVMInfo* info)
{
    CLObject self;

    self = create_field_object(type_object, NULL, NULL);

    CLOBJECT_HEADER(self)->mType = type_object;

    return self;
}

void initialize_hidden_class_method_of_method_object(sCLClass* klass)
{
    klass->mFreeFun = NULL;
    klass->mShowFun = NULL;
    klass->mMarkFun = NULL;
    klass->mCreateFun = create_method_object_for_new;
}

BOOL Method_setValue(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    CLObject value;
    int i;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue; // self

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    value = (lvar+1)->mObjectValue.mValue;

    if(!check_type_with_class_name(value, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    CLMETHOD(self)->mClass = CLMETHOD(value)->mClass;
    CLMETHOD(self)->mMethod = CLMETHOD(value)->mMethod;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isNativeMethod(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_NATIVE_METHOD);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isClassMethod(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_CLASS_METHOD);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isPrivateMethod(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_PRIVATE_METHOD);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isConstructor(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_CONSTRUCTOR);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isSyncronizedMethod(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_SYNCHRONIZED_METHOD);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isVirtualMethod(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_VIRTUAL_METHOD);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isAbstractMethod(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_ABSTRACT_METHOD);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isGenericsNewableConstructor(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_GENERICS_NEWABLE_CONSTRUCTOR);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isProtectedMethod(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_PROTECTED_METHOD);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_isParamVariableArguments(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLMethod* method;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    method = CLMETHOD(self)->mMethod;

    if(method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_bool_object(method->mFlags & CL_METHOD_PARAM_VARABILE_ARGUMENTS);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_name(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLClass* klass;
    sCLMethod* method;
    char* str;
    wchar_t* wstr;
    int wlen;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    klass = CLMETHOD(self)->mClass;
    method = CLMETHOD(self)->mMethod;

    if(klass == NULL || method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    str = CONS_str(&klass->mConstPool, method->mNameOffset);

    wlen = strlen(str)+1;
    wstr = MALLOC(sizeof(wchar_t)*wlen);

    if((int)mbstowcs(wstr, str, wlen) < 0) {
        entry_exception_object(info, gExConvertingStringCodeClass, "error mbstowcs on converting string");
        FREE(wstr);
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_string_object(wstr, wlen, gStringTypeObject, info);
    (*stack_ptr)++;

    FREE(wstr);

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_path(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLClass* klass;
    sCLMethod* method;
    char* str;
    wchar_t* wstr;
    int wlen;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    klass = CLMETHOD(self)->mClass;
    method = CLMETHOD(self)->mMethod;

    if(klass == NULL || method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    str = CONS_str(&klass->mConstPool, method->mPathOffset);

    wlen = strlen(str)+1;
    wstr = MALLOC(sizeof(wchar_t)*wlen);

    if((int)mbstowcs(wstr, str, wlen) < 0) {
        entry_exception_object(info, gExConvertingStringCodeClass, "error mbstowcs on converting string");
        FREE(wstr);
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = create_string_object(wstr, wlen, gStringTypeObject, info);
    (*stack_ptr)++;

    FREE(wstr);

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_resultType(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLClass* klass;
    sCLMethod* method;
    CLObject type_object;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    klass = CLMETHOD(self)->mClass;
    method = CLMETHOD(self)->mMethod;

    if(klass == NULL || method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    type_object = create_type_object_from_cl_type(klass, &method->mResultType, info);
    (*stack_ptr)->mObjectValue.mValue = type_object;
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_blockResultType(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    sCLClass* klass;
    sCLMethod* method;
    CLObject type_object;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    klass = CLMETHOD(self)->mClass;
    method = CLMETHOD(self)->mMethod;

    if(klass == NULL || method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    if(method->mBlockType.mResultType.mClassNameOffset == 0) {
        type_object = create_type_object_with_class_name("void");
    }
    else {
        type_object = create_type_object_from_cl_type(klass, &method->mBlockType.mResultType, info);
    }
    (*stack_ptr)->mObjectValue.mValue = type_object;
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_parametors(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    CLObject type_object;
    sCLClass* klass;
    CLObject array;
    CLObject array_type_object;
    CLObject type_object2;
    sCLMethod* method;
    int i;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue; // self

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    klass = CLMETHOD(self)->mClass;
    method = CLMETHOD(self)->mMethod;

    if(klass == NULL || method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    array_type_object = create_type_object_with_class_name("Array$1");
    push_object(array_type_object, info);

    type_object2 = create_type_object_with_class_name("Type");

    CLTYPEOBJECT(array_type_object)->mGenericsTypes[0] = type_object2;
    CLTYPEOBJECT(array_type_object)->mGenericsTypesNum = 1;

    array = create_array_object(array_type_object, NULL, 0, info);

    push_object(array, info);

    for(i=0; i<method->mNumParams; i++) {
        CLObject element;
        sCLType* param;

        param = method->mParamTypes + i;

        element = create_type_object_from_cl_type(klass, param, info);

        add_to_array(array, element, info);
    }

    pop_object(info);
    pop_object(info);

    (*stack_ptr)->mObjectValue.mValue = array;
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_blockParametors(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    CLObject type_object;
    sCLClass* klass;
    CLObject array;
    CLObject array_type_object;
    CLObject type_object2;
    sCLMethod* method;
    int i;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue; // self

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    klass = CLMETHOD(self)->mClass;
    method = CLMETHOD(self)->mMethod;

    if(klass == NULL || method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    array_type_object = create_type_object_with_class_name("Array$1");
    push_object(array_type_object, info);

    type_object2 = create_type_object_with_class_name("Type");

    CLTYPEOBJECT(array_type_object)->mGenericsTypes[0] = type_object2;
    CLTYPEOBJECT(array_type_object)->mGenericsTypesNum = 1;

    array = create_array_object(array_type_object, NULL, 0, info);

    push_object(array, info);

    for(i=0; i<method->mBlockType.mNumParams; i++) {
        CLObject element;
        sCLType* param;

        param = method->mBlockType.mParamTypes + i;

        element = create_type_object_from_cl_type(klass, param, info);

        add_to_array(array, element, info);
    }

    pop_object(info);
    pop_object(info);

    (*stack_ptr)->mObjectValue.mValue = array;
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Method_exceptions(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info, CLObject vm_type)
{
    CLObject self;
    CLObject type_object;
    sCLClass* klass;
    CLObject array;
    CLObject array_type_object;
    CLObject type_object2;
    sCLMethod* method;
    int i;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue; // self

    if(!check_type_with_class_name(self, "Method", info)) {
        vm_mutex_unlock();
        return FALSE;
    }

    klass = CLMETHOD(self)->mClass;
    method = CLMETHOD(self)->mMethod;

    if(klass == NULL || method == NULL) {
        entry_exception_object(info, gExNullPointerClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    array_type_object = create_type_object_with_class_name("Array$1");
    push_object(array_type_object, info);

    type_object2 = create_type_object_with_class_name("Type");

    CLTYPEOBJECT(array_type_object)->mGenericsTypes[0] = type_object2;
    CLTYPEOBJECT(array_type_object)->mGenericsTypesNum = 1;

    array = create_array_object(array_type_object, NULL, 0, info);

    push_object(array, info);

    for(i=0; i<method->mNumException; i++) {
        CLObject element;
        char* exceptin_class_name;

        exceptin_class_name = CONS_str(&klass->mConstPool, method->mExceptionClassNameOffset[i]);

        element = create_type_object_with_class_name(exceptin_class_name);

        add_to_array(array, element, info);
    }

    pop_object(info);
    pop_object(info);

    (*stack_ptr)->mObjectValue.mValue = array;
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}