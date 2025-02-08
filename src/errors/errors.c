
#include "errors.h"

#include <stdio.h>
#include <stdlib.h>

static const char *g_Errors_statusToStrMap[] = {[SUCCESS]                         = "Operation succeeded",
                                                [ERR_MEM_ALLOC]                   = "Memory allocation failed",
                                                [ERR_BAD_ARGUMENT]                = "Function called with a bad argument",
                                                [ERR_LIBRARY_NOT_INITIALIZED]     = "Library function called without initializing the library first",
                                                [ERR_LIBRARY_ALREADY_INITIALIZED] = "Library init function called second time",
                                                [ERR_ELEM_DATABASE_MISMATCH]      = "The given element does not belong to the given database",
                                                [ERR_DUPLICATE_ELEM]              = "The given element compares equal to another element already in the database",
                                                [ERR_CHECK_ERRNO]                 = "A call to a library function failed, errno is set appropriately",
                                                [ERR_INVALID_OPERATION]           = "The requested operation cannot be performed in the current state"};

#define ARRAY_LEN(array) (sizeof(array) / sizeof(*(array)))
_Static_assert(ARRAY_LEN(g_Errors_statusToStrMap) == ERR_COUNT,
               "Error: seems like a description string for an error is missing");

#define IS_KNOWN_STATUS(status) ((SUCCESS <= (status)) && ((status) < ERR_COUNT))

void Errors_assert(status_t status) {
    const char *errStr;
    if (status == SUCCESS) {
        return;
    }
    errStr = IS_KNOWN_STATUS(status) ? g_Errors_statusToStrMap[status] : "unknown error";
    (void)fprintf(stderr, "%s\n", errStr);
    exit((int)status);  // NOLINT (mute clang-tidy for 'concurrency-mt-unsafe' warning)
}

const char *Errors_getStr(status_t status) {
#ifdef C_ERRORS_SAFE_MODE
    if (!IS_KNOWN_STATUS(status)) {
        return NULL;
    }
#endif  // C_DATABASES_SAFE_MODE
    return g_Errors_statusToStrMap[status];
}
