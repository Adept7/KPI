package com.android.cslabs;
import java.util.LinkedList;

/**
 * Created with IntelliJ IDEA.
 * User: luka
 * Date: 13.09.13
 * Time: 13:09
 * To change this template use File | Settings | File Templates.
 */
public class Task {
    private int power;
    private LinkedList<Processor> processorList;

    private Task(int power, LinkedList<Processor> processorList){
        this.power = power;
        this.processorList = processorList;
    }


    public static Task generateTask(double minBound, double maxBound, LinkedList<Processor> processorList){
        int power = 0;
        LinkedList<Processor> currentProcessorList = new LinkedList<Processor>();


        //random of processors
        while (currentProcessorList.isEmpty()){
            for (Processor currentProcessor: processorList){
                if (Math.random() > 0.5) currentProcessorList.addLast(currentProcessor);
            }
        }

        //random of complexity
        double complexity = Math.random();
        while (complexity < (minBound/maxBound)) complexity = Math.random();

        power = ((Double)(complexity*maxBound)).intValue();

        return new Task(power,currentProcessorList);

    }

    public LinkedList<Processor> getProcessorList() {
        return processorList;
    }

    public int getPower() {
        return power;
    }

    public void setPower(int power) {
        this.power = power;
    }
}
