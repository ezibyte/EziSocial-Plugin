/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.hellocpp;

// Cocos2d-x
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

// Required to get hash-kay for Facebook app. Copy the generated hash key and add it to your Facebook App. Then you can delete the code related to hash key.
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;

// EziSocial Plugin
import com.ezibyte.social.EziSocialManager;

public class HelloCpp extends Cocos2dxActivity{
	
    protected void onCreate(Bundle savedInstanceState)
    {
		super.onCreate(savedInstanceState);
        
        // Try to get your hash key
        try {
		    PackageInfo info = getPackageManager().getPackageInfo("org.cocos2dx.hellocpp", PackageManager.GET_SIGNATURES);
		    for (Signature signature : info.signatures) {
		        MessageDigest md = MessageDigest.getInstance("SHA");
		        md.update(signature.toByteArray());
		        Log.e("MY KEY HASH:", Base64.encodeToString(md.digest(), Base64.DEFAULT));
		    }
		}
        catch (NameNotFoundException e)
        {
            
		}
        catch (NoSuchAlgorithmException e)
        {
		}
        
        // Initialize EziSocial Plugin Manager for Android.
        // ToDo Make sure you add the Facebook App ID in strings.xml file.
        EziSocialManager.initWithActivity(this,
                                          this.getApplicationContext().getString(R.string.app_id),
                                          true, // Set to see ezisocial plugin logs
                                          savedInstanceState
                                          );
	}
    
    public Cocos2dxGLSurfaceView onCreateView()
    {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// HelloCpp should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
    
    @Override
	protected void onResume()
	{
		super.onResume();
		EziSocialManager.applicationResumed();
	}
    
	@Override
	public void onPause()
	{
		super.onPause();
		EziSocialManager.applicationPaused();
	}
    
	@Override
	public void onDestroy()
	{
		super.onDestroy();
		EziSocialManager.applicationDestroyed();
	}
    
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		super.onActivityResult(requestCode, resultCode, data);
		EziSocialManager.onActivityResult(requestCode, resultCode, data);
        
	}
    
    static
    {
        System.loadLibrary("cocos2dcpp");
    }
}
