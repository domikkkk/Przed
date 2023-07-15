
package pl.ususweb.usus.controler.REST;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.util.Assert;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.entity.Group;
import pl.ususweb.usus.entity.Student;
import pl.ususweb.usus.service.ActivityService;
import pl.ususweb.usus.service.GroupService;
import pl.ususweb.usus.service.StudentService;

import java.util.List;

@RestController // This means that this class is a Controller
@RequestMapping("/group")
public class GroupController {
    @Autowired
    public GroupService groupService;
    @Autowired
    ActivityService activityService;

    @Autowired
    StudentService studentService;
    @PostMapping(path = "/add/{activity}", consumes = {MediaType.APPLICATION_FORM_URLENCODED_VALUE})
    public @ResponseBody
    RedirectView addNewGroup (@ModelAttribute Group group) {

        List<String> validWeekdays = List.of("Poniedziałek","Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela");

        // @ResponseBody means the returned String is the response, not a view name
        Assert.isTrue(group.getHour() < 24  && group.getHour() >= 0, "group hour must be between 0 and 24");
        Assert.isTrue( validWeekdays.stream().anyMatch(n -> n.equalsIgnoreCase(group.getWeekday())), "Invalid week day");
        Assert.isTrue( group.getStudents()==null || group.getStudents().size()<=group.getGroupSize(), "Group size exceeded");

        //group.setActivity(activityService.getActivity(Integer.parseInt(activity)));
        groupService.saveGroup(group);

        if (group.getStudents()!=null){
            for (Student student : group.getStudents()) {
                studentService.addGroup(student, group);
            }
        }
        return new RedirectView("/activity/list");
    }
}


