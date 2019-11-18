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
 * \brief �͹���ģʽ��˯�ߡ����˯�ߣ����̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1.������ʾ��ǰ���ڽ��е�ģʽ���ԣ����Ƚ���˯��ģʽ��
 *   2.���� KEY/RES����PIOA_7������ MCU,���������˯��ģʽ���ԡ�
 *   3.���� KEY/RES����PIOA_7������ MCU,LED��˸��MCU������������ģʽ��
 *
 * \note
 *   1.���Ա�����֮ǰӦ�� am_prj_config.h �еĺ� AM_CFG_SYSTEM_TICK_ENABLE��
 *     AM_CFG_SOFTIMER_ENABLE ��   AM_CFG_KEY_GPIO_ENABLE ����Ϊ 0��
 *   2.����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f03x_drv_lpmode_wake_up.c src_hc32f03x_drv_lpmode_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-15  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f03x_drv_lpmode_wake_up
 * \copydoc demo_hc32f03x_drv_lpmode_wake_up.c
 */

/** [src_hc32f03x_drv_lpmode_wake_up] */
#include "ametal.h"
#include "am_board.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hc32x3x_pin.h"
#include "am_hc32f03x_inst_init.h"
#include "demo_amf03x_core_entries.h"
#include "am_hc32_lpmode.h"

/**
 * \brief �����жϷ�����
 */
static void __gpio_isr (void *p_arg)
{
    ;
}

/**
 * \brief �������
 */
void demo_hc32f03x_drv_lpmode_wake_up_entry (void)
{
    AM_DBG_INFO("sleep mode test!\r\n");
    am_mdelay(100);

    /* �����ж����� */
    am_gpio_pin_cfg(PIOA_7, PIOA_7_INPUT_PU);
    am_gpio_trigger_connect(PIOA_7, __gpio_isr, NULL);
    am_gpio_trigger_cfg(PIOA_7, AM_GPIO_TRIGGER_FALL);
    am_gpio_trigger_on(PIOA_7);

    /* �͹���ģʽ��ʼ�� */
    am_hc32_lpmode_init();

    /* ˯��ģʽ��ϵͳʱ������ */
    am_hc32_lpmode_clk_change(AM_HC32_LPMODE_MODE_SLEEP);

    /* ����˯��ģʽ�����Ѻ��ٽ��� */
    am_hc32_lpmode_sleep(AM_FALSE);

    AM_DBG_INFO("sleep mode, wake_up!\r\n");

    AM_DBG_INFO("deepsleep mode test!\r\n");

    /* ˯��ģʽ��ϵͳʱ������ */
    am_hc32_lpmode_clk_change(AM_HC32_LPMODE_MODE_DEEPSLEEP);

    /* �������˯��ģʽ�����Ѻ��ٽ��� */
    am_hc32_lpmode_deepsleep(AM_FALSE);

    AM_DBG_INFO("deepsleep mode, wake_up!\r\n\r\n");

    while (1) {

        /* ָʾ��ָʾʱ���Ƿ�ָ����� */
        am_led_on(LED0);
        am_mdelay(500);
        am_led_off(LED0);
        am_mdelay(500);
    }
}
/** [src_hc32f03x_drv_lpmode_wake_up] */

/* end of file */