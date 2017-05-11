package com.android.cslabs;

import android.widget.SeekBar;

import java.util.ArrayList;

/**
 * Created with IntelliJ IDEA.
 * User: luka
 * Date: 17.09.13
 * Time: 10:29
 * To change this template use File | Settings | File Templates.
 */
public class GlobalParametrs {
    public static final int CAPACITY = 5;
    public static final int LEFT = 10;
    public static final int RIGHT = 200;
    private static double minBound = 0;
    private static double maxBound = 0;

    public static ArrayList<Integer> getPower() {
        return cpuPower;
    }

    private static ArrayList<Integer> cpuPower = new ArrayList<Integer>(CAPACITY);
    private static double probability = 0;
    private static int minimalPower = 0;

    public static void initialize(){
        for (int i = 0; i < CAPACITY; i++)
            cpuPower.add(0);
    }

    public static void setMinimalPower(){
        int minPower = cpuPower.get(0);

        for (Integer currentPower: cpuPower)
            if (currentPower < minPower) minPower = currentPower;

        minimalPower = minPower;
    }

    public static void setPower(int pos, Integer value){
        cpuPower.set(pos,value);
    }


    public static int getMinimalPower(){
        return minimalPower;
    }

    public static double getMinBound() {
        return minBound;
    }

    public static void setMinBound(double minnBound) {
        minBound = minnBound;
    }

    public static double getMaxBound() {
        return maxBound;
    }

    public static void setMaxBound(double maxxBound) {
        maxBound = maxxBound;
    }


    public static double getProbability() {
        return probability;
    }

    public static void setProbability(double pprobability) {
        probability = pprobability;
    }

}
