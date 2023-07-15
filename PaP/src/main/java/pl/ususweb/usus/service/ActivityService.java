package pl.ususweb.usus.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import pl.ususweb.usus.Repository.ActivityRepository;
import pl.ususweb.usus.entity.Activity;

import java.util.List;

@Service
public class ActivityService {
    @Autowired
    private ActivityRepository activityRepository;
    public void saveActivity(Activity activity){
        activityRepository.save(activity);
    }

    public Activity getActivity(int id){
        return activityRepository.findById(id).orElse(null);
    }

    public List<Activity> getActivities(){
        return activityRepository.findAll();
    }

    public void removeActivity(int id){
        activityRepository.deleteById(id);
    }

    public void setTrade(int id, boolean t){
        Activity activity = getActivity(id);
        activity.setStudentCanTrade(t);
        activityRepository.saveAndFlush(activity);
    }

}
