package org.raydelto.test;


import org.cocos2dx.simplegame.R;

import com.ast.jumpingbunny.SimpleGame;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;


public class TestActivity extends Activity{
	private Button btnJugar;	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
        
        
        setContentView(R.layout.activity_main);
        btnJugar = (Button) findViewById(R.id.btnJugar);
        btnJugar.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				startActivity(new Intent(TestActivity.this,SimpleGame.class));
				
			}
		});
        
	}

}
