package pl.ususweb.usus.controler.REST;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.entity.ExchangeOffer;
import pl.ususweb.usus.entity.Group;
import pl.ususweb.usus.entity.Student;
import pl.ususweb.usus.exception.ApiRequestException;
import pl.ususweb.usus.service.StudentService;
import pl.ususweb.usus.utils.DateConverter;


import java.util.List;

@RestController // This means that this class is a Controller
@RequestMapping("/student")
public class StudentController {

    // before parsing
    @AllArgsConstructor
    private static class StudentStr {

        private String firstname;

        private String lastname;

        private String birthdate;

        private String username;

        List<Group> studentGroups;

        List<ExchangeOffer> offers;
    }

    @Autowired
    public StudentService studentService;
    @PostMapping(path = "/add", consumes = {MediaType.APPLICATION_FORM_URLENCODED_VALUE}) // Map ONLY POST Requests
    public RedirectView addNewStudent(StudentStr notparsed) throws ApiRequestException {

        Student student = new Student();
        student.setBirthdate(DateConverter.parseDate(notparsed.birthdate));
        student.setStudentGroups(notparsed.studentGroups);
        student.setOffers(notparsed.offers);
        student.setFirstname(notparsed.firstname);
        student.setLastname(notparsed.lastname);
        student.setUsername(notparsed.username);
        // @ResponseBody means the returned String is the response, not a view name
        try {
            studentService.saveStudent(student);
            return new RedirectView("/student/list");
        }
        catch (Exception e){
            throw new ApiRequestException(e.getMessage(), e);
        }
    }

    @GetMapping("/all")
    public @ResponseBody Iterable<Student> getAllStudents() {
        // This returns a JSON or XML with the users
        return studentService.getStudents();
    }

    @GetMapping("/get/{id}")
    public @ResponseBody Student getStudent(@PathVariable("id") int id){
        return studentService.getStudent(id);
    }

    @GetMapping("/delete/{id}")
    public  RedirectView deleteUser (@PathVariable("id") Integer id){
        studentService.removeStudent(id);
        return new RedirectView("/student/list");
    }
    @PostMapping("/update/{id}")
    public RedirectView updateStudent(@PathVariable("id") Integer id,
                                @ModelAttribute("student") Student student)
    {
        // get student from database by id
        student.setIndeks(id);
        // save updated student object
        studentService.updateStudent(student);
        return new RedirectView("/student/list");
    }
}


