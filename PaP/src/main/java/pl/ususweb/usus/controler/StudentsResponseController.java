package pl.ususweb.usus.controler;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import pl.ususweb.usus.service.*;


// Annotation
@Controller
// Class
public class StudentsResponseController {
    @Autowired
    StudentService sService;

    @Autowired
    GroupService gService;
    @Autowired
    ExchangeOfferService eService;

    @Autowired
    StudentService service;

    @Autowired
    FinalGradeCalcService finalGradeCalcService;

    @GetMapping("/student/list") public String list(Model model)
    {
        model.addAttribute("students",service.getStudents());
        model.addAttribute("calc", finalGradeCalcService);

        return "all_students";
    }
    @GetMapping("/student/view") public String view(Model model)
    {
        model.addAttribute("students", service.getStudents());
        return "allStudents";
    }
    @GetMapping("/student/edit/{id}")
    public String editStudentForm(@PathVariable Integer id, Model model) {
        model.addAttribute("student", sService.getStudent(id));
        //model.addAttribute("periods", pService.getRegistrationPeriods());
        model.addAttribute("groups", gService.getGroups());
        return "edit_student";
    }
}
