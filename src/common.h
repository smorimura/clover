#ifndef COMMON_H
#define COMMON_H

#include <stdarg.h>

//////////////////////////////////////////////////
// heap.c
//////////////////////////////////////////////////
void heap_init(int heap_size, int size_hadles);
void heap_final();
void* object_to_ptr(CLObject obj);
CLObject alloc_object(unsigned int size);
void cl_gc();
void show_heap();
CLObject create_object(sCLClass* klass);
CLObject alloc_heap_mem(unsigned int size);
void mark_object(CLObject obj, unsigned char* mark_flg);

//////////////////////////////////////////////////
// klass.c
//////////////////////////////////////////////////
extern sCLNodeType gIntType;      // foudamental classes
extern sCLNodeType gFloatType;
extern sCLNodeType gVoidType;

extern sCLNodeType gStringType;
extern sCLNodeType gHashType;
extern sCLNodeType gArrayType;

extern sCLNodeType gAnonymousType[CL_GENERICS_CLASS_PARAM_MAX];;

extern sCLClass* gCloverClass;
sCLClass* alloc_class(char* namespace, char* class_name, BOOL private_, BOOL open_, char** generics_types, int generics_types_num);
BOOL add_method(sCLClass* klass, BOOL static_, BOOL private_, BOOL native_, char* name, sCLNodeType* result_type, sCLNodeType* class_params, unsigned int num_params, BOOL constructor);
BOOL check_super_class_offsets(sCLClass* klass);
void class_init(BOOL load_foundamental_class);
void class_final();
unsigned int get_hash(char* name);
void show_class(sCLClass* klass);
void show_all_classes();
BOOL save_class(sCLClass* klass);
void save_all_modified_class();
sCLClass* load_class_from_classpath(char* file_name);
ALLOC unsigned char* native_load_class(char* file_name);
void show_constants(sConst* constant);
void alloc_bytecode(sCLMethod* method);
void create_real_class_name(char* result, int result_size, char* namespace, char* class_name);
void increase_class_version(sCLClass* klass);

// result: (null) --> file not found (char* pointer) --> success
ALLOC char* load_file(char* file_name);

// result (TRUE) --> success (FALSE) --> overflow methods number or method parametor number
BOOL add_method(sCLClass* klass, BOOL static_, BOOL private_, BOOL native_, char* name, sCLNodeType* result_type, sCLNodeType* class_params, unsigned int num_params, BOOL constructor);

// result (TRUE) --> success (FLASE) --> overflow super class number 
BOOL add_super_class(sCLClass* klass, sCLClass* super_klass);

// result (TRUE) --> success (FALSE) --> overflow number fields
BOOL add_field(sCLClass* klass, BOOL static_, BOOL private_, char* name, sCLNodeType* type_);

// result: (NULL) not found (sCLClass*) found
sCLClass* get_super(sCLClass* klass);

// result: (NULL) --> not found (non NULL) --> field
sCLField* get_field(sCLClass* klass, char* field_name);

// result: (NULL) not found the method (sCLMethod*) found method. (sCLClass** founded_class) was setted on the method owner class.
sCLMethod* get_method_on_super_classes(sCLClass* klass, char* method_name, sCLClass** founded_class);

// result: (NULL) --> not found (non NULL) --> field
// also return the class in which is found the the field 
sCLField* get_field_including_super_classes(sCLClass* klass, char* field_name, sCLClass** founded_class);

// result: (-1) --> not found (non -1) --> field index
int get_field_index(sCLClass* klass, char* field_name);

// result: (-1) --> not found (non -1) --> field index
// also return the class which is found the index to found_class parametor
int get_field_index_including_super_classes(sCLClass* klass, char* field_name);

// result is seted on this parametors(sCLNodeType* result)
// if the field is not found, result->mClass is setted on NULL
void get_field_type(sCLClass* klass, sCLField* field, sCLNodeType* result, sCLNodeType* type_);

// return field number
int get_field_num_including_super_classes(sCLClass* klass);

// result: (NULL) --> not found (non NULL) --> method
sCLMethod* get_method(sCLClass* klass, char* method_name);

// result: (NULL) --> not found (non NULL) --> method
sCLMethod* get_method_from_index(sCLClass* klass, int method_index);

// result: (-1) --> not found (non -1) --> method index
int get_method_index(sCLClass* klass, sCLMethod* method);

// result: (-1) --> not found (non -1) --> method index
int get_method_index_from_the_parametor_point(sCLClass* klass, char* method_name, int method_index, BOOL search_for_class_method);

// result should be found
void get_param_type_of_method(sCLClass* klass, sCLMethod* method, int param_num, sCLNodeType* result);

// result: (FALSE) can't solve a generics type (TRUE) success
// if type_ is NULL, don't solve generics type
BOOL get_result_type_of_method(sCLClass* klass, sCLMethod* method, sCLNodeType* result, sCLNodeType* type_);

// result: (NULL) not found the method (sCLMethod*) found method. (sCLClass** founded_class) was setted on the method owner class
// if type_ is NULL, don't solve generics type
sCLMethod* get_virtual_method_with_params(sCLClass* klass, char* method_name, sCLNodeType* class_params, unsigned int num_params, sCLClass** founded_class, BOOL search_for_class_method, sCLNodeType* type_);

// result: (NULL) --> not found (non NULL) --> method
// if type_ is NULL, don't solve generics type
sCLMethod* get_method_with_type_params(sCLClass* klass, char* method_name, sCLNodeType* class_params, unsigned int num_params, BOOL search_for_class_method, sCLNodeType* type_, int start_point);

// result: (NULL) not found the method (sCLMethod*) found method. (sCLClass** foud_class) was setted on the method owner class.
sCLMethod* get_method_on_super_classes(sCLClass* klass, char* method_name, sCLClass** found_class);

// result: (TRUE) found (FALSE) not found
BOOL search_for_super_class(sCLClass* klass, sCLClass* searched_class);

// return method parametor number
int get_method_num_params(sCLMethod* method);

// result: (NULL) not found the method (sCLMethod*) found method. (sCLClass** founded_class) was setted on the method owner class.
// if type_ is NULL, don't solve generics type
sCLMethod* get_method_with_type_params_on_super_classes(sCLClass* klass, char* method_name, sCLNodeType* class_params, unsigned int num_params, sCLClass** founded_class, BOOL search_for_class_method, sCLNodeType* type_);

//////////////////////////////////////////////////
// parser.c
//////////////////////////////////////////////////
typedef struct {
    char mName[CL_METHOD_NAME_MAX];
    int mIndex;
    sCLNodeType mType;
} sVar;

typedef struct {
    sVar mLocalVariables[CL_LOCAL_VARIABLE_MAX];  // open address hash
    int mVarNum;
} sVarTable;

extern sVarTable gGVTable;       // global variable table

// result: (true) success (false) overflow the table
BOOL add_variable_to_table(sVarTable* table, char* name, sCLNodeType* type_);

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name);

void sBuf_init(sBuf* self);
void sBuf_append_char(sBuf* self, char c);
void sBuf_append(sBuf* self, void* str, size_t size);

void sConst_init(sConst* self);
void sConst_free(sConst* self);
void sConst_append_str(sConst* constant, char* str);
void sConst_append(sConst* self, void* data, unsigned int size);
void sConst_append_wstr(sConst* constant, char* str);
void sConst_append_int(sConst* constant, int n);

void sByteCode_init(sByteCode* self);
void sByteCode_free(sByteCode* self);
void sByteCode_append(sByteCode* self, void* code, unsigned int size);

void parser_init(BOOL load_foundamental_class);
void parser_final();

BOOL parse_word(char* buf, int buf_size, char** p, char* sname, int* sline, int* err_num);
void skip_spaces_and_lf(char** p, int* sline);
void skip_spaces(char** p);
void parser_err_msg(char* msg, char* sname, int sline);
void parser_err_msg_format(char* sname, int sline, char* msg, ...);
BOOL expect_next_character(char* characters, int* err_num, char** p, char* sname, int* sline);
// characters is null-terminated
void expect_next_character_with_one_forward(char* characters, int* err_num, char** p, char* sname, int* sline);

BOOL node_expression(unsigned int* node, char** p, char* sname, int* sline, int* err_num, sVarTable* lv_table, char* current_namespace, sCLClass* klass);

BOOL parse_generics_types_name(char** p, char* sname, int* sline, int* err_num, char* generics_types_num, sCLClass** generics_types, char* current_namespace, sCLClass* klass);

BOOL parse_namespace_and_class(sCLClass** result, char** p, char* sname, int* sline, int* err_num, char* current_namespace, sCLClass* klass);
    // result: (FALSE) there is an error (TRUE) success
    // result class is setted on first parametor
BOOL parse_namespace_and_class_and_generics_type(sCLNodeType* type, char** p, char* sname, int* sline, int* err_num, char* current_namespace, sCLClass* klass) ;
    // result: (FALSE) there is an error (TRUE) success
    // result type is setted on first parametor
int get_generics_type_num(sCLClass* klass, char* type_name);

BOOL delete_comment(sBuf* source, sBuf* source2);

//////////////////////////////////////////////////
// node.c
//////////////////////////////////////////////////
#define NODE_TYPE_OPERAND 1
#define NODE_TYPE_VALUE 2
#define NODE_TYPE_STRING_VALUE 3
#define NODE_TYPE_VARIABLE_NAME 4
#define NODE_TYPE_ARRAY_VALUE 5
#define NODE_TYPE_DEFINE_VARIABLE_NAME 7
#define NODE_TYPE_FIELD 8
#define NODE_TYPE_CLASS_FIELD 9
#define NODE_TYPE_STORE_VARIABLE_NAME 10
#define NODE_TYPE_DEFINE_AND_STORE_VARIABLE_NAME 11
#define NODE_TYPE_STORE_FIELD 12
#define NODE_TYPE_STORE_CLASS_FIELD 13
#define NODE_TYPE_CLASS_METHOD_CALL 14
#define NODE_TYPE_PARAM 15
#define NODE_TYPE_RETURN 16
#define NODE_TYPE_NEW 17
#define NODE_TYPE_METHOD_CALL 18
#define NODE_TYPE_SUPER 19
#define NODE_TYPE_INHERIT 20

enum eOperand { 
    kOpAdd, kOpSub, kOpMult, kOpDiv, kOpMod, kOpPlusPlus2, kOpMinusMinus2
};

typedef struct sNodeTreeStruct {
    unsigned char mNodeType;
    sCLNodeType mType;

    union {
        enum eOperand mOperand;
        int mValue;
        char* mStringValue;
        char* mVarName;
    } uValue;

    unsigned int mLeft;     // node index
    unsigned int mRight;
    unsigned int mMiddle;
} sNodeTree;

extern sNodeTree* gNodes; // All nodes at here. Index is node number. sNodeTree_create* functions return a node number.

BOOL compile_method(sCLMethod* method, sCLClass* klass, char** p, char* sname, int* sline, int* err_num, sVarTable* lv_table, BOOL constructor, char* current_namespace);
// left_type is stored calss. right_type is class of value.
BOOL type_checking(sCLNodeType* left_type, sCLNodeType* right_type);
BOOL type_checking_with_class(sCLClass* left_type, sCLClass* right_type);
BOOL type_identity(sCLNodeType* type1, sCLNodeType* type2);

// Below functions return a node number. It is an index of gNodes.
unsigned int sNodeTree_create_operand(enum eOperand operand, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_value(int value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_string_value(MANAGED char* value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_array(unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_var(char* var_name, sCLNodeType* klass, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_define_var(char* var_name, sCLNodeType* klass, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_return(sCLNodeType* klass, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_class_method_call(char* var_name, sCLNodeType* klass, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_class_field(char* var_name, sCLNodeType* klass, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_param(unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_new_expression(sCLNodeType* klass, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_fields(char* name, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_method_call(char* var_name, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_super(unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_inherit(unsigned int left, unsigned int right, unsigned int middle);

//////////////////////////////////////////////////
// vm.c
//////////////////////////////////////////////////
extern MVALUE* gCLStack;
extern int gCLStackSize;
extern MVALUE* gCLStackPtr;

#define INVOKE_METHOD_KIND_CLASS 0
#define INVOKE_METHOD_KIND_OBJECT 1

//////////////////////////////////////////////////
// string.c
//////////////////////////////////////////////////
CLObject alloc_string_object(unsigned int len);
unsigned int string_size(CLObject string);
CLObject create_string_object(wchar_t* str, unsigned int len);

//////////////////////////////////////////////////
// array.c
//////////////////////////////////////////////////
CLObject alloc_array_object(unsigned int array_size);
unsigned int array_size(CLObject array);
CLObject create_array_object(MVALUE elements[], unsigned int elements_len);
void mark_array_object(CLObject object, unsigned char* mark_flg);

//////////////////////////////////////////////////
// xfunc.c
//////////////////////////////////////////////////
char* xstrncpy(char* des, char* src, int size);
char* xstrncat(char* des, char* str, int size);

//////////////////////////////////////////////////
// object.c
//////////////////////////////////////////////////
unsigned int object_size(sCLClass* klass);
CLObject create_object(sCLClass* klass);
void mark_user_object(CLObject object, unsigned char* mark_flg);

#endif
