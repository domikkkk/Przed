package pl.ususweb.usus.controler.REST;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.entity.Activity;
import pl.ususweb.usus.service.ActivityService;

@RestController // This means that this class is a Controller
@RequestMapping("activity")
public class ActivityController {
    @Autowired
    public ActivityService activityService;

    @AllArgsConstructor
    static class CheckboxConvert {
        String name;
        String description;
        String studentCanTrade;
    }
    @PostMapping(path = "/add", consumes = {MediaType.APPLICATION_FORM_URLENCODED_VALUE})
    public RedirectView addNewActivity (@ModelAttribute CheckboxConvert notConverted) {

        Activity act = new Activity();
        act.setName(notConverted.name);
        act.setDescription(notConverted.description);
        act.setStudentCanTrade(notConverted.studentCanTrade!=null); // this is epitome of urlencoded data
        activityService.saveActivity(act);
        return new RedirectView("/activity/list");
    }

    @GetMapping("/all")
    public @ResponseBody Iterable<Activity> getAllActivities() {

        return activityService.getActivities();
    }

    @GetMapping("/get/{id}")
    public @ResponseBody Activity activity(@PathVariable("id") int id){
        return activityService.getActivity(id);
    }

    @GetMapping("/delete/{id}")
    public RedirectView removeActivity (@PathVariable("id") int id){
        activityService.removeActivity(id);
        return new RedirectView("/activity/list");
    }
}


