package com.android.cslabs;

import android.app.Activity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.*;

import java.util.ArrayList;

public class MainActivity extends Activity implements View.OnClickListener, SeekBar.OnSeekBarChangeListener {
    /**
     * Called when the activity is first created.
     */


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        GlobalParametrs.initialize();
        final Button startButton = (Button) findViewById(R.id.startButton);
        startButton.setOnClickListener(this);
        final SeekBar probabilitySeekBar = (SeekBar) findViewById(R.id.probabilitySeekBar);
        probabilitySeekBar.setOnSeekBarChangeListener(this);
        final SeekBar minBoundSeekBar = (SeekBar) findViewById(R.id.minBoundSeekBar);
        minBoundSeekBar.setOnSeekBarChangeListener(this);
        final SeekBar maxBoundSeekBar = (SeekBar) findViewById(R.id.maxBoundSeekBar);
        maxBoundSeekBar.setOnSeekBarChangeListener(this);

        ArrayList<EditText> editTexts = new ArrayList<EditText>();
        editTexts.add((EditText) findViewById(R.id.firstCPUPowerEditText));
        editTexts.add((EditText) findViewById(R.id.secondCPUPowerEditText));
        editTexts.add((EditText) findViewById(R.id.thirdCPUPowerEditText));
        editTexts.add((EditText) findViewById(R.id.fourthCPUPowerEditText));
        editTexts.add((EditText) findViewById(R.id.fifthCPUPowerEditText));

        for (int i = 0; i < editTexts.size(); i++) {

            final int pos = i;

            editTexts.get(pos).addTextChangedListener(new TextWatcher() {

                @Override
                public void beforeTextChanged(CharSequence charSequence, int i, int i2, int i3) {
                }

                @Override
                public void onTextChanged(CharSequence charSequence, int i, int i2, int i3) {
                }

                @Override
                public void afterTextChanged(Editable editable) {
                    GlobalParametrs.setPower(pos, Integer.valueOf(editable.toString()));
                    GlobalParametrs.setMinimalPower();
                    rewriteMinSeekBar();
                    rewriteMaxSeekBar();
                }
            });
        }

    }

    private void rewriteMinSeekBar() {
        SeekBar minBoundSeekBar = (SeekBar) findViewById(R.id.minBoundSeekBar);
        TextView minBoundPercentText = (TextView) findViewById(R.id.minBoundTextPercent);
        GlobalParametrs.setMinBound(GlobalParametrs.getMinimalPower() * (((double) (GlobalParametrs.RIGHT - GlobalParametrs.LEFT) / 100) * minBoundSeekBar.getProgress() + GlobalParametrs.LEFT));
        minBoundPercentText.setText(String.valueOf(GlobalParametrs.getMinBound()));
    }

    private void rewriteMaxSeekBar() {
        SeekBar maxBoundSeekBar = (SeekBar) findViewById(R.id.maxBoundSeekBar);
        TextView maxBoundPercentText = (TextView) findViewById(R.id.maxBoundTextPercent);
        GlobalParametrs.setMaxBound(((GlobalParametrs.RIGHT * GlobalParametrs.getMinimalPower() - GlobalParametrs.getMinBound()) / 100) * maxBoundSeekBar.getProgress() + GlobalParametrs.getMinBound());
        maxBoundPercentText.setText(String.valueOf(GlobalParametrs.getMaxBound()));
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.startButton:

                Simulation FIFO = new Simulation(GlobalParametrs.getPower().get(0),
                        GlobalParametrs.getPower().get(1),
                        GlobalParametrs.getPower().get(2),
                        GlobalParametrs.getPower().get(3),
                        GlobalParametrs.getPower().get(4),
                        GlobalParametrs.getProbability(),
                        GlobalParametrs.getMinBound(),
                        GlobalParametrs.getMaxBound());

                FIFO.runSimulation();
                ListView listView = (ListView) findViewById(R.id.listView);
                listView.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, FIFO.getResult()));
                break;
        }
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
        switch (seekBar.getId()) {
            case R.id.probabilitySeekBar:
                final TextView probabilityTextPercent = (TextView) findViewById(R.id.probabilityTextPercent);
                GlobalParametrs.setProbability(seekBar.getProgress() / 100.0);
                probabilityTextPercent.setText(String.valueOf(GlobalParametrs.getProbability()));
                break;
            case R.id.minBoundSeekBar:
                rewriteMinSeekBar();
                rewriteMaxSeekBar();
                break;
            case R.id.maxBoundSeekBar:
                rewriteMaxSeekBar();
                break;
        }
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {
        //cap
    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        //Cap
    }


}
