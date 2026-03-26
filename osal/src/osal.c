/*******************************************************************************
 * @file        osal.c
 * @author      Sarath S
 * @brief       OS abstraction layer implementation
 *
 * @details
 * This file connects the OSAL interface with the platform-specific
 * implementation provided by the user.
 *
 * It does not contain any OS-specific logic.
 ******************************************************************************/

/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "osal.h"

/*******************************************************************************
 * Functions
 *******************************************************************************/

/**
 * @brief Initialize OSAL instance
 */
osal_err_t osal_init(osal_t *osal, const osal_ops_t *ops)
{
    /* Basic validation */
    if ((osal == NULL) || (ops == NULL))
    {
        return OSAL_ERR_NULL_PTR;
    }

    /* Store ops */
    osal->ops = ops;
    osal->ctx = NULL;

    /* Optional init */
    if (osal->ops->init)
    {
        return osal->ops->init(osal);
    }

    return OSAL_OK;
}

/**
 * @brief Deinitialize OSAL instance
 */
osal_err_t osal_deinit(osal_t *osal)
{
    if ((osal == NULL) || (osal->ops == NULL))
    {
        return OSAL_ERR_NULL_PTR;
    }

    /* Optional deinit */
    if (osal->ops->deinit)
    {
        return osal->ops->deinit(osal);
    }

    return OSAL_OK;
}

/****************************** End of file ***********************************/