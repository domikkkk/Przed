package pl.ususweb.usus.controler;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import pl.ususweb.usus.entity.Student;
import pl.ususweb.usus.service.ActivityService;
import pl.ususweb.usus.service.StudentService;

import java.security.Principal;

@Controller
public class ActivityResponseController {
    @Autowired
    ActivityService aService;

    @Autowired
    StudentService studentService;
    @GetMapping("/activity/list") public String get(Model model)
    {
        model.addAttribute("activities",aService.getActivities());

        return "all_activities";
    }


    @GetMapping("/activity/list/student") public String studentTimetable(Model model, Principal principal)
    {
        Student currentStudent = studentService.getStudentByUsername(principal.getName());
        model.addAttribute("groups",currentStudent.getStudentGroups());

        return "all_groups_student";
    }

}
