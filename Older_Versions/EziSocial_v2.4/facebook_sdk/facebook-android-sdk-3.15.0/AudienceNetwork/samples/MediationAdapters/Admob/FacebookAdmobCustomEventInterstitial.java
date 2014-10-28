package com.facebook.ads;

import android.app.Activity;
import com.google.ads.mediation.MediationAdRequest;
import com.google.ads.mediation.customevent.CustomEventInterstitial;
import com.google.ads.mediation.customevent.CustomEventInterstitialListener;

/**
 * FacebookAdmobCustomEventInterstitial is an admob adapter for InterstitialAd.
 * <p/>
 * Compatible with Google Mobile Ads SDK version 6.4.1
 * <p/>
 * Declare com.facebook.ads.InterstitialAdActivity in AndroidManifest.xml
 * with android:configChanges="keyboardHidden|orientation"
 */
public class FacebookAdmobCustomEventInterstitial implements CustomEventInterstitial, InterstitialAdListener {

    private InterstitialAd mInterstitialAd;
    private CustomEventInterstitialListener mInterstitialListener;

    @Override
    public void requestInterstitialAd(CustomEventInterstitialListener customEventInterstitialListener,
                                      Activity activity, String label, String serverParameter,
                                      MediationAdRequest mediationAdRequest, Object o) {
        mInterstitialListener = customEventInterstitialListener;

        // Assuming placement_id is configured in serverParameter.
        String placementId = serverParameter;
        if (placementId == null || placementId.length() == 0) {
            // Invalid placement_id
            mInterstitialListener.onFailedToReceiveAd();
            return;
        }

        mInterstitialAd = new InterstitialAd(activity, placementId);
        mInterstitialAd.setAdListener(this);
        mInterstitialAd.loadAd();
    }

    @Override
    public void showInterstitial() {
        mInterstitialAd.show();
    }

    @Override
    public void destroy() {
        if (mInterstitialAd != null) {
            mInterstitialAd.destroy();
            mInterstitialAd = null;
        }
    }

    @Override
    public void onInterstitialDisplayed(Ad ad) {
        mInterstitialListener.onPresentScreen();
    }

    @Override
    public void onInterstitialDismissed(Ad ad) {
        mInterstitialListener.onDismissScreen();
    }

    @Override
    public void onError(Ad ad, AdError adError) {
        mInterstitialListener.onFailedToReceiveAd();
    }

    @Override
    public void onAdLoaded(Ad ad) {
        mInterstitialListener.onReceivedAd();
    }

    @Override
    public void onAdClicked(Ad ad) {
        mInterstitialListener.onLeaveApplication();
    }
}
