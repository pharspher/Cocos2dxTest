/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

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
package org.ph.deckbattle;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

public class MainActivity extends Cocos2dxActivity {

    private static Handler mHandler= new Handler();

    public static native void onLeaveDialogConfirmed();
    public static native void onLeaveDialogCanceled();

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    static {
         System.loadLibrary("game");
    }

    public static void showLeaveDialog() {
        Log.d("roger_tag", "showLeaveDialog()");
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                DialogFragment dialog = new LocalDialogFragment();
                dialog.show(((MainActivity)getContext()).getFragmentManager(), "dialog");
                /*
                Dialog dialog = new AlertDialog.Builder(getContext())
                    .setTitle(R.string.leave_dialog_title)
                    .setMessage(R.string.leave_dialog_message)
                    .setPositiveButton(R.string.leave_dialog_yes, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface arg0, int arg1) {
                            
                        }
                    })
                    .setNegativeButton(R.string.leave_dialog_no, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface arg0, int arg1) {
                            
                        }
                    })
                    .create();
                dialog.setCanceledOnTouchOutside(false);
                dialog.show();
                */
            }
        });
    }

    public static class LocalDialogFragment extends DialogFragment {

        @Override
        public Dialog onCreateDialog(Bundle savedInstanceState) {
            Dialog dialog = new AlertDialog.Builder(getContext())
            .setTitle(R.string.leave_dialog_title)
            .setMessage(R.string.leave_dialog_message)
            .setPositiveButton(R.string.leave_dialog_yes, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface arg0, int arg1) {
                    onLeaveDialogConfirmed();
                }
            })
            .setNegativeButton(R.string.leave_dialog_no, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface arg0, int arg1) {
                    onLeaveDialogCanceled();
                }
            })
            .create();
            dialog.setCanceledOnTouchOutside(false);
            return dialog;
        }
    };
}
