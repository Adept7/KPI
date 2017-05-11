package com.android.cslabs;
import java.util.LinkedList;

/**
 * Created with IntelliJ IDEA.
 * User: luka
 * Date: 13.09.13
 * Time: 15:32
 * To change this template use File | Settings | File Templates.
 */
public class Scheduler {

    private static LinkedList<Task> taskList = new LinkedList<Task>();

    private Scheduler(){

    }

    public static void planFIFO(Task task){

        if (task != null)
            taskList.addFirst(task);

        Processor powerProc = null;

        for (Processor currentProc: taskList.getLast().getProcessorList()){
            if (!currentProc.isBusy()) {
                powerProc = currentProc;
                break;
            }
        }

        if (powerProc == null) return;
        powerProc.setCurrentTask(taskList.removeLast());
    }

    public static void clearTaskList(){
        taskList.clear();
    }

    public static Task getTaskFIFO(Processor processor){
        if (taskList.isEmpty()) return null;
        if (taskList.getLast().getProcessorList().contains(processor))
            return taskList.removeLast();
        return null;
    }
}
