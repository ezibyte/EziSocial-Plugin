package com.facebook.ads;

import android.app.Activity;
import android.content.Context;
import com.mopub.mobileads.CustomEventBanner;
import com.mopub.mobileads.MoPubErrorCode;

import java.util.Map;

/**
 * FacebookMopubCustomEventBanner is a MoPub banner adapter for AdView.
 * <p/>
 * Compatible with mopub-android-sdk version 1.17.3.1
 */
public class FacebookMopubCustomEventBanner extends CustomEventBanner implements AdListener {

    private AdView mAdView;
    private CustomEventBannerListener mBannerListener;

    @Override
    protected void loadBanner(Context context, CustomEventBannerListener customEventBannerListener,
                              Map<String, Object> localExtras, Map<String, String> serverExtras) {
        mBannerListener = customEventBannerListener;

        if (!(context instanceof Activity)) {
            mBannerListener.onBannerFailed(MoPubErrorCode.ADAPTER_CONFIGURATION_ERROR);
            return;
        }

        // Assuming placement_id is configured in serverExtras with key placement_id.
        String placementId = serverExtras.get("placement_id");
        if (placementId == null || placementId.length() == 0) {
            // Invalid placement_id
            mBannerListener.onBannerFailed(MoPubErrorCode.ADAPTER_CONFIGURATION_ERROR);
            return;
        }

        mAdView = new AdView(context, placementId, AdSize.BANNER_320_50);
        mAdView.setAdListener(this);
        mAdView.loadAd();
    }

    @Override
    protected void onInvalidate() {
        if (mAdView != null) {
            mAdView.destroy();
            mAdView = null;
        }
    }

    @Override
    public void onError(Ad ad, AdError error) {
        if (error.getErrorCode() == AdError.NO_FILL.getErrorCode()) {
            mBannerListener.onBannerFailed(MoPubErrorCode.NETWORK_NO_FILL);
        } else if (error == AdError.INTERNAL_ERROR) {
            mBannerListener.onBannerFailed(MoPubErrorCode.NETWORK_INVALID_STATE);
        } else {
            mBannerListener.onBannerFailed(MoPubErrorCode.UNSPECIFIED);
        }
    }

    @Override
    public void onAdLoaded(Ad ad) {
        mBannerListener.onBannerLoaded(mAdView);
    }

    @Override
    public void onAdClicked(Ad ad) {
        mBannerListener.onBannerClicked();
    }
}
