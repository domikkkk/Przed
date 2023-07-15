package pl.ususweb.usus.controler.REST;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.entity.Activity;
import pl.ususweb.usus.entity.Grade;
import pl.ususweb.usus.entity.GradedTest;
import pl.ususweb.usus.service.ActivityService;
import pl.ususweb.usus.service.GradedTestService;
import pl.ususweb.usus.service.StudentService;
import pl.ususweb.usus.utils.DateConverter;

import java.time.LocalDate;
import java.util.List;

@AllArgsConstructor
class GradedTestStr {
    Integer Id;

    String Title;

    Activity activity;

    Float maxPoints;

    String date;


}

@RequestMapping("gradedTest")
@RestController
public class GradedTestController {
    @AllArgsConstructor
    static class GradePair {
        Integer owner;
        Float result;
    }

    @Autowired
    private GradedTestService testService;

    @Autowired
    private ActivityService activityService;
    @Autowired
    private StudentService studentService;

    //@TODO: does this need ModelAttribute?
    @PostMapping(path = "/add/{activityId}", consumes = {MediaType.APPLICATION_FORM_URLENCODED_VALUE})
    public @ResponseBody RedirectView addNewGradedTest(GradedTestStr notparsed, @PathVariable int activityId){
        GradedTest t = new GradedTest();
        LocalDate when = DateConverter.parseDate(notparsed.date);
        t.setTestDate(when);
        t.setActivity(activityService.getActivity(activityId));
        t.setTitle(notparsed.Title);
        t.setMaxPoints(notparsed.maxPoints);
        testService.saveGradedTest(t);
        return new RedirectView("/gradedTest/list");
    }

    @GetMapping("/all")
    public @ResponseBody Iterable<GradedTest> getAllTests() {

        return testService.getGradedTests();
    }

    @GetMapping("/purgeGrades/{id}")
    public @ResponseBody String submitGrades(@PathVariable("id") int id)
    {
        GradedTest test = testService.getGradedTest(id);
        testService.purgeGradesForTest(test);
        return "Usunięto wszystkie oceny z bazy";
    }

    //takes list of studentId:grade pairs and updates repository with it
    @PostMapping(path="/submitGrades/{id}", consumes = MediaType.APPLICATION_JSON_VALUE)
    public @ResponseBody String submitGrades(@PathVariable("id") int id, @RequestBody List<GradePair> gradeList){

        GradedTest test = testService.getGradedTest(id);
        testService.purgeGradesForTest(test);
        for (GradePair pair : gradeList){
            Grade grade = new Grade();
            grade.setOwner(studentService.getStudent(pair.owner));
            grade.setResult(pair.result);
            grade.setGradedTest(test);
            testService.saveGrade(grade);
        }
        return "Zapisano oceny";
    }

    @GetMapping("/get/{id}")
    public @ResponseBody GradedTest getGradedTest(@PathVariable("id") int id){
        return testService.getGradedTest(id);
    }

    @GetMapping("/delete/{id}")
    public RedirectView removeGraded (@PathVariable("id") int id){
        return  testService.removeGradedTest(id);
    }
}
