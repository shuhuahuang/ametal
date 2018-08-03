/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief MX25XX ����
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����Խ����
 *
 * \par Դ����
 * \snippet demo_mx25xx.c src_mx25xx
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mx25xx
 * \copydoc demo_mx25xx.c
 */

/** [src_mx25xx] */
#include "ametal.h"
#include "am_delay.h"
#include "am_mx25xx.h"
#include "am_vdebug.h"

#define __BUF_SIZE 16 /**< \brief ��������С */

/**
 * \brief �������
 */
void demo_mx25xx_entry (am_mx25xx_handle_t mx25xx_handle, int32_t test_lenth)
{
    int     ret;
    uint8_t i;
    uint8_t wr_buf[__BUF_SIZE] = {0}; /* д���ݻ��涨�� */
    uint8_t rd_buf[__BUF_SIZE] = {0}; /* �����ݻ��涨�� */

    if (__BUF_SIZE < test_lenth) {
        test_lenth = __BUF_SIZE;
    }

    /* ��䷢�ͻ����� */
    for (i = 0;i < test_lenth; i++) {
        wr_buf[i] = i;
    }

    /* �������� */
    am_mx25xx_erase(mx25xx_handle, 0x001000, test_lenth);

    /* д���� */
    ret = am_mx25xx_write(mx25xx_handle, 0x001000, &wr_buf[0], test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_mx25xx_write error(id: %d).\r\n", ret);
        return;
    }
    am_mdelay(5);

    /* ������ */
    ret = am_mx25xx_read(mx25xx_handle, 0x001000, &rd_buf[0], test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_mx25xx_read error(id: %d).\r\n", ret);
        return;
    }

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0; i < test_lenth; i++) {
        AM_DBG_INFO("Read FLASH the %2dth data is %2x\r\n", i ,rd_buf[i]);

        /* У��ʧ�� */
        if(wr_buf[i] != rd_buf[i]) {
            AM_DBG_INFO("verify failed at index %d.\r\n", i);
            break;
        }
    }

    if (test_lenth == i) {
        AM_DBG_INFO("verify success!\r\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_mx25xx] */

/* end of file */