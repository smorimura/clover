#include "clover.h"
#include "common.h"
#include <stdlib.h>
#include <wchar.h>
#include <limits.h>
#include <unistd.h>

BOOL Clover_print(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info)
{
    MVALUE* string;
    int size;
    char* str;

    vm_mutex_lock();

    string = lvar;

    if(string->mIntValue == 0) {
        entry_exception_object(info, gExNullPointerType.mClass, "Null pointer exception");
        vm_mutex_unlock();
        return FALSE;
    }

    size = (CLSTRING(string->mObjectValue)->mLen + 1) * MB_LEN_MAX;
    str = MALLOC(size);
    if((int)wcstombs(str, CLSTRING(string->mObjectValue)->mChars, size) < 0) {
        FREE(str);
        entry_exception_object(info, gExConvertingStringCodeType.mClass, "wcstombs");
        vm_mutex_unlock();
        return FALSE;
    }

    cl_print("%s", str);

    FREE(str);

    vm_mutex_unlock();

    return TRUE;
}

BOOL Clover_show_classes(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info)
{
    show_class_list();

    return TRUE;
}

BOOL Clover_output_to_str(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info)
{
    CLObject block;
    sBuf buf;
    BOOL result_existance_of_method;
    wchar_t* wstr;
    char* str;
    int len;
    int wcs_len;
    BOOL result_existance;
    sBuf* cl_print_buffer_before;

    vm_mutex_lock();

    result_existance = FALSE;

    block = lvar->mObjectValue;

    cl_print_buffer_before = gCLPrintBuffer;
    gCLPrintBuffer = &buf;              // allocate
    sBuf_init(gCLPrintBuffer);

    if(!cl_excute_block(block, NULL, result_existance, TRUE, info)) {
        FREE(gCLPrintBuffer->mBuf);
        gCLPrintBuffer = cl_print_buffer_before;
        vm_mutex_unlock();
        return FALSE;
    }

    str = gCLPrintBuffer->mBuf;

    len = strlen(str) + 1;
    wstr = MALLOC(sizeof(wchar_t)*len);
    if((int)mbstowcs(wstr, str, len) < 0) {
        FREE(wstr);
        FREE(gCLPrintBuffer->mBuf);

        entry_exception_object(info, gExConvertingStringCodeType.mClass, "mbstowcs");
        gCLPrintBuffer = cl_print_buffer_before;
        vm_mutex_unlock();
        return FALSE;
    }
    wcs_len = wcslen(wstr);

    (*stack_ptr)->mObjectValue = create_string_object(gStringType.mClass, wstr, wcs_len);
    (*stack_ptr)++;

    FREE(wstr);
    FREE(gCLPrintBuffer->mBuf);

    gCLPrintBuffer = cl_print_buffer_before;

    vm_mutex_unlock();

    return TRUE;
}


