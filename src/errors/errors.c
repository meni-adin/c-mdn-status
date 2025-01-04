
#include "errors.h"

#include <stdio.h>
#include <stdlib.h>

static const char *gErrorsDatabase[] = {[SUCCESS]                    = "Operation succeeded",
                                        [ERR_MEM_ALLOC]              = "Memory allocation failed",
                                        [ERR_BAD_ARGUMENT]           = "Function called with a bad argument",
                                        [ERR_ELEM_DATABASE_MISMATCH] = "The given element does not belong to the given database",
                                        [ERR_DUPLICATE_ELEM]         = "The given element compares equal to another element already in the database",
                                        [ERR_DOUBLE_INIT]            = "Init function called second time without an intervening call to deinit",
                                        [ERR_DEINIT_WITHOUT_INIT]    = "Deinit function called without a previous call to init"};

#define ARRAY_LEN(array) (sizeof(array) / sizeof(*(array)))

#define IS_KNOWN_STATUS(status) ((SUCCESS <= (status)) && ((status) < ERR_COUNT))

_Static_assert(ARRAY_LEN(gErrorsDatabase) == ERR_COUNT,
               "Error: seems like a description string for an error is missing");

void Errors_assert(status_t status) {
    const char *errStr;
    if (status == SUCCESS) {
        return;
    }
    errStr = IS_KNOWN_STATUS(status) ? gErrorsDatabase[status] : "unknown error";
    (void)fprintf(stderr, "%s\n", errStr);
    exit((int)status);  // NOLINT (mute clang-tidy for 'concurrency-mt-unsafe' warning)
}

const char *Errors_getStr(status_t status) {
#ifdef C_ERRORS_SAFE_MODE
    if (!IS_KNOWN_STATUS(status)) {
        return NULL;
    }
#endif  // C_DATABASES_SAFE_MODE
    return gErrorsDatabase[status];
}
