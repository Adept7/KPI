package com.android.cslabs;
/**
 * Created with IntelliJ IDEA.
 * User: luka
 * Date: 13.09.13
 * Time: 13:18
 * To change this template use File | Settings | File Templates.
 */
public class Processor {
    private int Power;

    private Task currentTask;
    private int implementedOperations;
    private int implementedTasks;

    public Processor(int Power){
        this.Power = Power;
        implementedOperations = 0;
        implementedTasks = 0;
    }

    public void setCurrentTask(Task currentTask) {
        this.currentTask = currentTask;
    }

    public boolean isBusy(){
        return currentTask == null ? false : true;
    }

    public int getPower() {
        return Power;
    }

    public void handling(){

        if (currentTask == null)
            return;

        recursiveCalc(Power);

    }

    private void recursiveCalc(int Power) {
        if (currentTask.getPower() > Power){
            currentTask.setPower(currentTask.getPower() - Power);
            implementedOperations += Power;
        }
        else {
            int remainingPower = Power - currentTask.getPower();
            implementedOperations += currentTask.getPower();
            currentTask.setPower(0);
            ++implementedTasks;

            currentTask = Scheduler.getTaskFIFO(this);
            if (currentTask == null) return;
            recursiveCalc(remainingPower);
        }
    }

    public int getImplementedOperations() {
        return implementedOperations;
    }

    public int getImplementedTasks() {
        return implementedTasks;
    }

    public void clearTaskList() {
        currentTask = null;
        implementedTasks = 0;
        implementedOperations = 0;
    }
}
