
#ifndef MDN_STATUS_H
#define MDN_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "mdn_status_config.h"

typedef enum mdn_Status_t_ {
    MDN_STATUS_SUCCESS = 0,  // Must be first and equal 0
    MDN_STATUS_ERROR_MEM_ALLOC,
    MDN_STATUS_ERROR_BAD_ARGUMENT,
    MDN_STATUS_ERROR_LIBRARY_NOT_INITIALIZED,
    MDN_STATUS_ERROR_LIBRARY_ALREADY_INITIALIZED,
    MDN_STATUS_ERROR_ELEM_DATABASE_MISMATCH,
    MDN_STATUS_ERROR_DUPLICATE_ELEM,
    MDN_STATUS_ERROR_CHECK_ERRNO,
    MDN_STATUS_ERROR_INVALID_OPERATION,
    MDN_STATUS_ENUM_COUNT,  // Must be last
} mdn_Status_t;

/**
 * @brief Assert that the given status is MDN_STATUS_SUCCESS,
 * otherwise print the status' message and exit the program with the status value.
 *
 * @param[in] status - the status to assert.
 */
void mdn_Status_assert(mdn_Status_t status);

/**
 * @brief Retrieve the string describing the given status.
 *
 * @param status - the status to get the description for.
 */
const char *mdn_Status_getStr(mdn_Status_t status);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // MDN_STATUS_H
