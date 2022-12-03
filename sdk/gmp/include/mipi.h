/*
 * Copyright (c) Hunan Goke,Chengdu Goke,Shandong Goke. 2021. All rights reserved.
 */

#ifndef __MIPI_RX_H__
#define __MIPI_RX_H__

typedef unsigned int combo_dev_t;
typedef unsigned int sns_rst_source_t;
typedef unsigned int sns_clk_source_t;


#define MIPI_LANE_NUM           4
#define LVDS_LANE_NUM           4

#define WDR_VC_NUM              2
#define SYNC_CODE_NUM           4

#define MIPI_RX_MAX_DEV_NUM     1
#define CMOS_MAX_DEV_NUM        1

#define SNS_MAX_CLK_SOURCE_NUM  1
#define SNS_MAX_RST_SOURCE_NUM  1


#ifdef MIPI_DEBUG
#define MSG(x...) \
    do { \
        osal_printk("%s->%d: ", __FUNCTION__, __LINE__); \
        osal_printk(x); \
        osal_printk("\n"); \
    } while (0)
#else
#define MSG(args...) do { } while (0)
#endif

#define ERR(x...) \
    do { \
        osal_printk("%s(%d): ", __FUNCTION__, __LINE__); \
        osal_printk(x); \
    } while (0)

#define MIPIRX_CHECK_NULL_PTR(ptr)\
    do{\
        if((ptr) == NULL)\
        {\
            ERR("NULL point \r\n");\
            return GK_FAILURE;\
        }\
    } while (0)


typedef enum {
    LANE_DIVIDE_MODE_0    = 0,
    LANE_DIVIDE_MODE_BUTT
} lane_divide_mode_t;

typedef enum {
    WORK_MODE_LVDS          = 0x0,
    WORK_MODE_MIPI          = 0x1,
    WORK_MODE_CMOS          = 0x2,
    WORK_MODE_BT1120        = 0x3,
    WORK_MODE_SLVS          = 0x4,
    WORK_MODE_BUTT
} work_mode_t;

typedef enum {
    INPUT_MODE_MIPI         = 0x0,
    INPUT_MODE_SUBLVDS      = 0x1,
    INPUT_MODE_LVDS         = 0x2,
    INPUT_MODE_HISPI        = 0x3,
    INPUT_MODE_CMOS         = 0x4,
    INPUT_MODE_BT601        = 0x5,
    INPUT_MODE_BT656        = 0x6,
    INPUT_MODE_BT1120       = 0x7,
    INPUT_MODE_BYPASS       = 0x8,
    INPUT_MODE_BUTT
} input_mode_t;

typedef enum {
    MIPI_DATA_RATE_X1 = 0,
    MIPI_DATA_RATE_X2 = 1,

    MIPI_DATA_RATE_BUTT
} mipi_data_rate_t;

typedef struct {
    int x;
    int y;
    unsigned int width;
    unsigned int height;
} img_rect_t;

typedef struct {
    unsigned int width;
    unsigned int height;
} img_size_t;

typedef enum {
    DATA_TYPE_RAW_8BIT = 0,
    DATA_TYPE_RAW_10BIT,
    DATA_TYPE_RAW_12BIT,
    DATA_TYPE_RAW_14BIT,
    DATA_TYPE_RAW_16BIT,
    DATA_TYPE_YUV420_8BIT_NORMAL,
    DATA_TYPE_YUV420_8BIT_LEGACY,
    DATA_TYPE_YUV422_8BIT,
    DATA_TYPE_BUTT
} data_type_t;

typedef enum {
    MIPI_WDR_MODE_NONE = 0x0,
    MIPI_WDR_MODE_VC   = 0x1,
    MIPI_WDR_MODE_DT   = 0x2,
    MIPI_WDR_MODE_DOL  = 0x3,
    MIPI_WDR_MODE_BUTT
} mipi_wdr_mode_t;



typedef struct {
    data_type_t           input_data_type;
    mipi_wdr_mode_t       wdr_mode;
    short                 lane_id[MIPI_LANE_NUM];

    union {
        short data_type[WDR_VC_NUM];
    };
} mipi_dev_attr_t;

typedef enum {
    IN_WDR_MODE_NONE    = 0x0,
    IN_WDR_MODE_2F      = 0x1,
    IN_WDR_MODE_3F      = 0x2,
    IN_WDR_MODE_4F      = 0x3,
    IN_WDR_MODE_DOL_2F  = 0x4,
    IN_WDR_MODE_DOL_3F  = 0x5,
    IN_WDR_MODE_DOL_4F  = 0x6,
    IN_WDR_MODE_BUTT
} wdr_mode_t;

typedef enum {
    LVDS_SYNC_MODE_SOF = 0,
    LVDS_SYNC_MODE_SAV,
    LVDS_SYNC_MODE_BUTT
} lvds_sync_mode_t;

typedef enum {
    LVDS_VSYNC_NORMAL   = 0x00,
    LVDS_VSYNC_SHARE    = 0x01,
    LVDS_VSYNC_HCONNECT = 0x02,
    LVDS_VSYNC_BUTT
} lvds_vsync_type_t;

typedef struct {
    lvds_vsync_type_t sync_type;

    unsigned short hblank1;
    unsigned short hblank2;
} lvds_vsync_attr_t;

typedef enum {
    LVDS_FID_NONE    = 0x00,
    LVDS_FID_IN_SAV  = 0x01,
    LVDS_FID_IN_DATA = 0x02,
    LVDS_FID_BUTT
} lvds_fid_type_t;

typedef struct {
    lvds_fid_type_t fid_type;

    unsigned char output_fil;
} lvds_fid_attr_t;

typedef enum {
    LVDS_ENDIAN_LITTLE  = 0x0,
    LVDS_ENDIAN_BIG     = 0x1,
    LVDS_ENDIAN_BUTT
} lvds_bit_endian_t;


typedef struct {
    data_type_t         input_data_type;
    wdr_mode_t          wdr_mode;

    lvds_sync_mode_t    sync_mode;
    lvds_vsync_attr_t   vsync_attr;
    lvds_fid_attr_t     fid_attr;

    lvds_bit_endian_t   data_endian;
    lvds_bit_endian_t   sync_code_endian;
    short               lane_id[LVDS_LANE_NUM];

    unsigned short      sync_code[LVDS_LANE_NUM][WDR_VC_NUM][SYNC_CODE_NUM];
} lvds_dev_attr_t;

typedef struct {
    combo_dev_t         devno;
    input_mode_t        input_mode;
    mipi_data_rate_t    data_rate;
    img_rect_t          img_rect;

    union {
        mipi_dev_attr_t     mipi_attr;
        lvds_dev_attr_t     lvds_attr;
    };
} combo_dev_attr_t;

typedef enum {
    PHY_CMV_GE1200MV    = 0x00,
    PHY_CMV_LT1200MV    = 0x01,
    PHY_CMV_BUTT
} phy_cmv_mode_t;

typedef struct {
    combo_dev_t       devno;
    phy_cmv_mode_t    cmv_mode;
} phy_cmv_t;


#define MIPI_IOC_MAGIC   'm'

#define MIPI_SET_DEV_ATTR                _IOW(MIPI_IOC_MAGIC, 0x01, combo_dev_attr_t)

#define MIPI_SET_PHY_CMVMODE             _IOW(MIPI_IOC_MAGIC, 0x04, phy_cmv_t)

#define MIPI_RESET_SENSOR                _IOW(MIPI_IOC_MAGIC, 0x05, sns_rst_source_t)

#define MIPI_UNRESET_SENSOR              _IOW(MIPI_IOC_MAGIC, 0x06, sns_rst_source_t)

#define MIPI_RESET_MIPI                  _IOW(MIPI_IOC_MAGIC, 0x07, combo_dev_t)

#define MIPI_UNRESET_MIPI                _IOW(MIPI_IOC_MAGIC, 0x08, combo_dev_t)

#define MIPI_RESET_SLVS                  _IOW(MIPI_IOC_MAGIC, 0x09, combo_dev_t)

#define MIPI_UNRESET_SLVS                _IOW(MIPI_IOC_MAGIC, 0x0a, combo_dev_t)

#define MIPI_SET_HS_MODE                 _IOW(MIPI_IOC_MAGIC, 0x0b, lane_divide_mode_t)

#define MIPI_ENABLE_MIPI_CLOCK           _IOW(MIPI_IOC_MAGIC, 0x0c, combo_dev_t)

#define MIPI_DISABLE_MIPI_CLOCK          _IOW(MIPI_IOC_MAGIC, 0x0d, combo_dev_t)

#define MIPI_ENABLE_SLVS_CLOCK           _IOW(MIPI_IOC_MAGIC, 0x0e, combo_dev_t)

#define MIPI_DISABLE_SLVS_CLOCK          _IOW(MIPI_IOC_MAGIC, 0x0f, combo_dev_t)

#define MIPI_ENABLE_SENSOR_CLOCK         _IOW(MIPI_IOC_MAGIC, 0x10, sns_clk_source_t)

#define MIPI_DISABLE_SENSOR_CLOCK        _IOW(MIPI_IOC_MAGIC, 0x11, sns_clk_source_t)

#endif
