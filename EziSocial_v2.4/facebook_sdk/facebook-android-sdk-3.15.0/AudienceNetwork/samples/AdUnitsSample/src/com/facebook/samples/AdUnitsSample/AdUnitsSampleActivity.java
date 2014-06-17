/**
 * Copyright 2010-present Facebook.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.facebook.samples.AdUnitsSample;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import com.facebook.ads.*;

public class AdUnitsSampleActivity extends Activity implements InterstitialAdListener {

    private RelativeLayout adViewContainer;
    private TextView adStatusLabel;
    private TextView interstitialAdStatusLabel;
    private Button loadInterstitialButton;
    private Button showInterstitialButton;

    private AdView adView;
    private InterstitialAd interstitialAd;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ad_sample);

        adViewContainer = (RelativeLayout) findViewById(R.id.adViewContainer);
        adStatusLabel = (TextView)findViewById(R.id.adStatusLabel);
        interstitialAdStatusLabel = (TextView)findViewById(R.id.interstitialAdStatusLabel);
        loadInterstitialButton = (Button)findViewById(R.id.loadInterstitialButton);
        showInterstitialButton = (Button)findViewById(R.id.showInterstitialButton);

        // When testing on a device, add its hashed ID to force test ads.
        // The hash ID is printed to log cat when running on a device and loading an ad.
        // AdSettings.addTestDevice("THE HASHED ID AS PRINTED TO LOG CAT");

        // Create a banner's ad view with a unique placement ID (generate your own on the Facebook app settings).
        // Use different ID for each ad placement in your app.
        adView = new AdView(this, "YOUR_PLACEMENT_ID", AdSize.BANNER_320_50);

        // Set a listener to get notified on changes or when the user interact with the ad.
        adView.setAdListener(this);

        // Reposition the ad and add it to the view hierarchy.
        adViewContainer.addView(adView);

        // Initiate a request to load an ad.
        adView.loadAd();

        loadInterstitialButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                interstitialAdStatusLabel.setText("Loading interstitial ad...");

                // Create the interstitial unit with a placement ID (generate your own on the Facebook app settings).
                // Use different ID for each ad placement in your app.
                interstitialAd = new InterstitialAd(AdUnitsSampleActivity.this, "YOUR_PLACEMENT_ID");

                // Set a listener to get notified on changes or when the user interact with the ad.
                interstitialAd.setAdListener(AdUnitsSampleActivity.this);

                // Load a new interstitial.
                interstitialAd.loadAd();
            }
        });

        showInterstitialButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (interstitialAd == null || !interstitialAd.isAdLoaded()) {
                    // Ad not ready to show.
                    interstitialAdStatusLabel.setText("Ad not loaded. Click load to request an ad.");
                } else {
                    // Ad was loaded, show it!
                    interstitialAd.show();
                    interstitialAdStatusLabel.setText("");
                }
            }
        });
    }

    @Override
    protected void onDestroy() {
        adView.destroy();
        if (interstitialAd != null) {
            interstitialAd.destroy();
        }
        super.onDestroy();
    }

    @Override
    public void onError(Ad ad, AdError error) {
        if (ad == adView) {
            adStatusLabel.setText("Ad failed to load: " + error.getErrorMessage());
        } else if (ad == interstitialAd) {
            interstitialAdStatusLabel.setText("Interstitial ad failed to load: " + error.getErrorMessage());
        }
    }

    @Override
    public void onAdLoaded(Ad ad) {
        if (ad == adView) {
            adStatusLabel.setText("");
        } else if (ad == interstitialAd) {
            interstitialAdStatusLabel.setText("Ad loaded. Click show to present!");
        }
    }

    @Override
    public void onInterstitialDisplayed(Ad ad) {
        Toast.makeText(this, "Interstitial Displayed", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onInterstitialDismissed(Ad ad) {
        Toast.makeText(this, "Interstitial Dismissed", Toast.LENGTH_SHORT).show();

        //Optional, cleanup.
        interstitialAd.destroy();
        interstitialAd = null;
    }

    @Override
    public void onAdClicked(Ad ad) {
        Toast.makeText(this, "Ad Clicked", Toast.LENGTH_SHORT).show();
    }
}
