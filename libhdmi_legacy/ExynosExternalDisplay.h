#ifndef EXYNOS_LEGACY_HDMI_H
#define EXYNOS_LEGACY_HDMI_H

#include "ExynosHWC.h"
#include "ExynosDisplay.h"

#define VIDEO_LAYER_INDEX       2
#define NUM_VIRT_OVER_HDMI 5

#define SUPPORTED_DV_TIMINGS_NUM 33

class ExynosExternalDisplay : public ExynosDisplay {
    public:
        /* Methods */
        ExynosExternalDisplay(struct exynos5_hwc_composer_device_1_t *pdev);
        ~ExynosExternalDisplay();

        void setHdmiStatus(bool status);

        bool isPresetSupported(unsigned int preset);
        int getConfig();
        int enableLayer(hdmi_layer_t &hl);
        void disableLayer(hdmi_layer_t &hl);
        int enable();
        void disable();
        int output(hdmi_layer_t &hl, hwc_layer_1_t &layer, private_handle_t *h, int acquireFenceFd, int *releaseFenceFd);
        void skipStaticLayers(hwc_display_contents_1_t *contents, int ovly_idx);
        void setPreset(int preset);
        int convert3DTo2D(int preset);
        void calculateDstRect(int src_w, int src_h, int dst_w, int dst_h, struct v4l2_rect *dst_rect);
        void setHdcpStatus(int status);
        void setAudioChannel(uint32_t channels);
        uint32_t getAudioChannel();
        int getDVTimingsIndex(int preset);
        int getCecPaddr();
        bool isVideoOverlaySupported(hwc_layer_1_t &layer, int format);
        bool isVPSupported(hwc_layer_1_t &layer, int format);

        bool isLayerBetweenGLES(hwc_display_contents_1_t* contents, size_t layerIndex);
        int clearDisplay();
        virtual int openHdmi();
        virtual int blank();
        virtual int prepare(hwc_display_contents_1_t* contents);
        virtual int set(hwc_display_contents_1_t* contents);

        virtual int waitForRenderFinish(private_module_t *grallocModule, buffer_handle_t *handle, int buffers);

        /* Fields */
        ExynosMPPModule         *mMPPs[1];

        int                     mMixer;
        bool                    mEnabled;
        bool                    mBlanked;
        hdmi_layer_t            mMixerLayers[3];
        int                     mIsFbLayer;
        int                     mIsVideoLayer;
        int                     mFbStarted;
        int                     mVideoStarted;
        bool                    mHasFbComposition;
        bool                    mHasSkipLayer;
        int                     mUiIndex;
        int                     mVideoIndex;
        bool                    mUseSubtitles;
        const void              *mLastLayerHandles[NUM_VIRT_OVER_HDMI];
        int                     mVirtualOverlayFlag;
};

#endif
