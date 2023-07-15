package pl.ususweb.usus.controler.REST;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import pl.ususweb.usus.entity.FinalGradeSettings;
import pl.ususweb.usus.service.AnnouncementService;
import pl.ususweb.usus.service.FinalGradeSettingsService;
import pl.ususweb.usus.service.GroupService;
import pl.ususweb.usus.service.StudentService;

import java.security.Principal;

@Controller // This means that this class is a Controller
@AllArgsConstructor
public class MainPage {
    GroupService groupService;
    StudentService studentService;
    AnnouncementService announcementService;

    FinalGradeSettingsService finalGradeSettingsService;

    @GetMapping(value={"/","/index.html", "/main"})
    public String mainPage(Principal principal, Model model){
        String name = finalGradeSettingsService.getFinalGradeSettings().getCourseName();
        model.addAttribute("courseName",name!=null ? name : "Strona przedmiotu");
        if (studentService.checkIfUsernameExists(principal.getName()))
        {
            // student
            return "mainStudent";
        }
        // prowadzacy
        return "main";
    }

    @GetMapping("/activity/new")
    public String addActivity(){
        return "add_activity";
    }

    @GetMapping("/group/new/{id}")
    public String addGroup(Model model, @PathVariable("id") Integer id){
        model.addAttribute("activity", id);
        model.addAttribute("students", studentService.getStudents());
        return "add_group";
    }

    @GetMapping("/student/new")
    public String addStudent(Model model, @Value("${usus.dateFormat}") String dateFormat){
        model.addAttribute("groups", groupService.getGroups());
        model.addAttribute("dateFormat", dateFormat);
        return "add_student";
    }
    @GetMapping("/dashboard")
    public String dashboard(Model model, Principal principal){
        model.addAttribute("announcements", announcementService.getAnnouncements());

        if (studentService.checkIfUsernameExists(principal.getName()))
        {
            // student
            return "dashboard_student";
        }
        // prowadzacy
        return "dashboard";
    }
}


