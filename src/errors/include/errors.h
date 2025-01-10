
#ifndef ERRORS_H
#define ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "c_errors_config.h"

typedef enum status_t_ {
    SUCCESS = 0,  // Must be first and equal 0
    ERR_MEM_ALLOC,
    ERR_BAD_ARGUMENT,
    ERR_LIBRARY_NOT_INITIALIZED,
    ERR_LIBRARY_ALREADY_INITIALIZED,
    ERR_ELEM_DATABASE_MISMATCH,
    ERR_DUPLICATE_ELEM,
    ERR_COUNT,  // Must be last
} status_t;

/**
 * @brief Assert that the given status is SUCCESS,
 * otherwise print the status' message and exit the program with the status value.
 *
 * @param[in] status - the status to assert.
 */
void Errors_assert(status_t status);

/**
 * @brief Retrieve the string describing the given status.
 *
 * @param status - the status to get the description for.
 */
const char *Errors_getStr(status_t status);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // ERRORS_H
