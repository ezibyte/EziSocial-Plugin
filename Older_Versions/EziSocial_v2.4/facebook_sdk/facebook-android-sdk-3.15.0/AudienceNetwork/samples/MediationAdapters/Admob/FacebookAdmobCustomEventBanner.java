package com.facebook.ads;

import android.app.Activity;
import com.google.ads.AdSize;
import com.google.ads.mediation.MediationAdRequest;
import com.google.ads.mediation.customevent.CustomEventBanner;
import com.google.ads.mediation.customevent.CustomEventBannerListener;

/**
 * FacebookAdmobCustomEventBanner is an admob adapter for AdView.
 * <p/>
 * Compatible with Google Mobile Ads SDK version 6.4.1
 */
public class FacebookAdmobCustomEventBanner implements CustomEventBanner, AdListener {

    private AdView mAdView;
    private CustomEventBannerListener mBannerListener;

    @Override
    public void requestBannerAd(CustomEventBannerListener customEventBannerListener, Activity activity,
                                String label, String serverParameter, AdSize adSize,
                                MediationAdRequest mediationAdRequest, Object o) {
        mBannerListener = customEventBannerListener;

        // Assuming placement_id is configured in serverParameter.
        String placementId = serverParameter;
        if (placementId == null || placementId.length() == 0) {
            // Invalid placement_id
            mBannerListener.onFailedToReceiveAd();
            return;
        }

        mAdView = new AdView(activity, placementId, com.facebook.ads.AdSize.BANNER_320_50);
        mAdView.setAdListener(this);
        mAdView.loadAd();
    }

    @Override
    public void destroy() {
        if (mAdView != null) {
            mAdView.destroy();
            mAdView = null;
        }
    }

    @Override
    public void onError(Ad ad, AdError adError) {
        mBannerListener.onFailedToReceiveAd();
    }

    @Override
    public void onAdLoaded(Ad ad) {
        mBannerListener.onReceivedAd(mAdView);
    }

    @Override
    public void onAdClicked(Ad ad) {
        mBannerListener.onClick();
    }
}
