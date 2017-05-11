package com.android.cslabs;
import android.app.Activity;
import android.content.res.Resources;
import android.text.Editable;

import java.util.LinkedList;

/**
 * Created with IntelliJ IDEA.
 * User: luka
 * Date: 13.09.13
 * Time: 19:30
 * To change this template use File | Settings | File Templates.
 */
public class Simulation{
    private static final int SIMULATION_CYCLE_ITERATION = 10000;
    private static final int NUMBER_OF_EXPERIMENTS = 5;
    private static final int MIN_MILISEC = 10;
    private static final int MAX_MILISEC = 200;

    public Simulation(int powerOne, int powerTwo, int powerThree, int powerFour, int powerFive, double probability, double minBound, double maxBound) {
        this.powerOne = powerOne;
        this.powerTwo = powerTwo;
        this.powerThree = powerThree;
        this.powerFour = powerFour;
        this.powerFive = powerFive;
        this.probability = probability;
        this.minBound = minBound;
        this.maxBound = maxBound;
        processorListInitializing();
    }

    private double minBound;
    private double maxBound;
    private int powerOne;
    private int powerTwo;
    private int powerThree;
    private int powerFour;
    private int powerFive;
    private double probability;
    private LinkedList<Processor> processorList;
    private String [] result;



    /*public Simulation() {
        powerOne = 5;
        powerTwo = 5;
        powerThree = 5;
        powerFour = 5;
        powerFive = 5;
        probability = 0.1;
        processorListInitializing();
        boundInitializing();
    }*/

    public void runSimulation(){


        double averageImplementedTasks = 0;
        double averageImplementedOperations = 0;
        double efficiency = 0;
        double sumPower = 0;
        int generatedTasks = 0;

        for (int i =0; i < NUMBER_OF_EXPERIMENTS ; i++){

            for (int j = 0; j < SIMULATION_CYCLE_ITERATION; j++){

                //generationg and planning of the task
                if (Math.random() < probability){
                    Task genTask = Task.generateTask(minBound, maxBound, processorList);
                    if (genTask != null) ++generatedTasks;
                    Scheduler.planFIFO(genTask);
                }

                for (Processor currentProcessor:processorList){
                    currentProcessor.handling();
                }
            }

            //counting the average values: sum all the operations and tasks
            for (Processor currentProcessor:processorList){
                averageImplementedTasks += currentProcessor.getImplementedTasks();
                averageImplementedOperations += currentProcessor.getImplementedOperations();
                currentProcessor.clearTaskList();
            }

        }

        //counting the average values: dividing the sum by number of experiments
        averageImplementedTasks /= NUMBER_OF_EXPERIMENTS;
        averageImplementedOperations /= NUMBER_OF_EXPERIMENTS;
        generatedTasks /= NUMBER_OF_EXPERIMENTS;

        for (Processor currentProcessor:processorList){
            sumPower += currentProcessor.getPower();
            currentProcessor.clearTaskList();
        }

        sumPower *= SIMULATION_CYCLE_ITERATION;

        efficiency = averageImplementedOperations/sumPower;

        Scheduler.clearTaskList();

        result = new String[]{"implemented operations = " + averageImplementedOperations,
        "generated tasks = " + generatedTasks,
        "implemented tasks = " + averageImplementedTasks,
        "Sum power of processors = " + sumPower,
        "efficiency = " + efficiency};

    }

    private void boundInitializing() {

        minBound = processorList.getFirst().getPower();
        maxBound = processorList.getFirst().getPower();

        for (Processor currentProcessor:processorList){
            if (currentProcessor.getPower() < minBound) minBound = currentProcessor.getPower();
            if (currentProcessor.getPower() > maxBound) maxBound = currentProcessor.getPower();
        }

        minBound *= MIN_MILISEC;
        maxBound *= MAX_MILISEC;
    }

    private void processorListInitializing() {
        processorList = new LinkedList<Processor>();
        processorList.addLast(new Processor(powerOne));
        processorList.addLast(new Processor(powerTwo));
        processorList.addLast(new Processor(powerThree));
        processorList.addLast(new Processor(powerFour));
        processorList.addLast(new Processor(powerFive));
    }

    public String[] getResult() {
        return result;
    }
}
