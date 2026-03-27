/*******************************************************************************
 * @file        osal.h
 * @author      Sarath S
 * @brief       Simple OS abstraction layer (OSAL)
 *
 * @details
 * Provides a small abstraction for OS-related features like delays,
 * locking, and ISR detection. Keeps drivers independent of the OS.
 *
 * The actual implementation (FreeRTOS, bare-metal, etc.) is supplied
 * by the application using an operations table.
 ******************************************************************************/

#ifndef OSAL_H
#define OSAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Includes
 *******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Types
 *******************************************************************************/

/** OSAL return codes */
typedef enum
{
    OSAL_OK = 0,
    OSAL_ERR_NULL_PTR = -1,
    OSAL_ERR_INVALID_ARGS = -2,
    OSAL_ERR_NOT_IMPD = -3
} osal_err_t;

typedef struct osal osal_t;

/**
 * @brief OSAL operations
 *
 * All functions are optional unless your platform requires them.
 */
typedef struct
{
    osal_err_t (*init)(osal_t *osal);
    osal_err_t (*deinit)(osal_t *osal);

    osal_err_t (*lock)(void);
    osal_err_t (*unlock)(void);

    bool (*is_isr)(void);
    uint32_t (*get_timestamp)(void);
    const char *(*get_thread_name)(void);

    void (*delay_ms)(uint32_t ms);
    void (*delay_ns)(uint32_t ns);

} osal_ops_t;

/** OSAL instance */
struct osal
{
    const osal_ops_t *ops;   /**< Function table */
    void *ctx;               /**< Optional user context */
};

/*******************************************************************************
 * API
 *******************************************************************************/

/**
 * @brief Initialize OSAL
 */
osal_err_t osal_init(osal_t *osal, const osal_ops_t *ops);

/**
 * @brief Deinitialize OSAL
 */
osal_err_t osal_deinit(osal_t *osal);

/**
 * @brief Get osal opts
 */
const osal_ops_t *get_osal_ops(void);

#ifdef __cplusplus
}
#endif

#endif /* OSAL_H */

/****************************** End of file ***********************************/
