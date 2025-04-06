
#include "mdn_status.h"

#include <stdio.h>
#include <stdlib.h>

static const char *g_mdn_Status_statusToStrMap[] = {[MDN_STATUS_SUCCESS]                           = "Operation succeeded",
                                                    [MDN_STATUS_ERROR_MEM_ALLOC]                   = "Memory allocation failed",
                                                    [MDN_STATUS_ERROR_BAD_ARGUMENT]                = "Function called with a bad argument",
                                                    [MDN_STATUS_ERROR_LIBRARY_NOT_INITIALIZED]     = "Library function called without initializing the library first",
                                                    [MDN_STATUS_ERROR_LIBRARY_ALREADY_INITIALIZED] = "Library init function called second time",
                                                    [MDN_STATUS_ERROR_ELEM_DATABASE_MISMATCH]      = "The given element does not belong to the given database",
                                                    [MDN_STATUS_ERROR_DUPLICATE_ELEM]              = "The given element compares equal to another element already in the database",
                                                    [MDN_STATUS_ERROR_CHECK_ERRNO]                 = "A call to a library function failed, errno is set appropriately",
                                                    [MDN_STATUS_ERROR_INVALID_OPERATION]           = "The requested operation cannot be performed in the current state"};

#define ARRAY_LEN(array) (sizeof(array) / sizeof(*(array)))
_Static_assert(ARRAY_LEN(g_mdn_Status_statusToStrMap) == MDN_STATUS_ENUM_COUNT,
               "Error: seems like a description string for a status is missing");

#define IS_KNOWN_STATUS(status) ((MDN_STATUS_SUCCESS <= (status)) && ((status) < MDN_STATUS_ENUM_COUNT))

void mdn_Status_assert(mdn_Status_t status) {
    const char *errStr;
    if (status == MDN_STATUS_SUCCESS) {
        return;
    }
    errStr = IS_KNOWN_STATUS(status) ? g_mdn_Status_statusToStrMap[status] : "unknown status";
    (void)fprintf(stderr, "%s\n", errStr);
    exit((int)status);  // NOLINT (mute clang-tidy for 'concurrency-mt-unsafe' warning)
}

const char *mdn_Status_getStr(mdn_Status_t status) {
#ifdef MDN_STATUS_SAFE_MODE
    if (!IS_KNOWN_STATUS(status)) {
        return NULL;
    }
#endif  // C_DATABASES_SAFE_MODE
    return g_mdn_Status_statusToStrMap[status];
}
