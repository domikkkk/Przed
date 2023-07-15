package pl.ususweb.usus.controler;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import pl.ususweb.usus.entity.Grade;
import pl.ususweb.usus.entity.GradedTest;
import pl.ususweb.usus.entity.Group;
import pl.ususweb.usus.entity.Student;
import pl.ususweb.usus.service.ActivityService;
import pl.ususweb.usus.service.FinalGradeSettingsService;
import pl.ususweb.usus.service.GradedTestService;
import pl.ususweb.usus.service.StudentService;
import pl.ususweb.usus.service.FinalGradeCalcService;

import java.security.Principal;
import java.util.ArrayList;

@Controller
@RequestMapping("/gradedTest")
public class GradedTestResponseController {

    @Autowired
    GradedTestService gradedTestService;

    @Autowired
    ActivityService activityService;

    @Autowired
    StudentService studentService;

    @Autowired
    FinalGradeSettingsService finalGradeSettingsService;

    @Autowired
    FinalGradeCalcService finalGradeCalcService;

    @GetMapping("/add/{actId}")
    public String add(@PathVariable Integer actId, Model model)
    {
        model.addAttribute("activity",activityService.getActivity(actId));
        return "add_graded_test";
    }

    // requires prowadzacy account
    @GetMapping("/list")
    public String listAll(Model model)
    {
        model.addAttribute("tests",gradedTestService.getGradedTests());
        return "all_tests";
    }

    @AllArgsConstructor
    static public class GradeHelper
    {
        public GradedTest test;
        public String resultStr;
    }

    // requires student account
    @GetMapping("/list/student")
    public String listAllForStudent(Model model, Principal principal)
    {
        //@TODO: Figure out which student I am
        Student currentStudent = studentService.getStudentByUsername(principal.getName());


        ArrayList<GradedTest> studentTests = (ArrayList<GradedTest>) gradedTestService.findGradedTestsByStudent(currentStudent);

        ArrayList<GradeHelper> modelGrades = new ArrayList<>();
        for (GradedTest test : studentTests)
        {
            Grade gradeForThisTest = gradedTestService.findGradeByGradedTestAndStudent(test,currentStudent);
            GradeHelper gh = new GradeHelper(test,"Brak");
            if (gradeForThisTest!=null){
                gh.resultStr=String.valueOf(gradeForThisTest.getResult());
            }
            modelGrades.add(gh);
        }
        model.addAttribute("testsAndGrades",modelGrades);
        model.addAttribute("finalGrade", finalGradeCalcService.finalGradeForStudent(currentStudent));
        return "all_tests_student";
    }


    @GetMapping("/editor/{testId}")
    public String gradeEditor(@PathVariable Integer testId,Model model)
    {

        GradedTest test = gradedTestService.getGradedTest(testId);

        ArrayList<Student> eligible = new ArrayList<>();

        for (Group g : test.getActivity().getActivityGroups()){
            eligible.addAll(g.getStudents());
        }

        ArrayList<Grade> grades = (ArrayList<Grade>) gradedTestService.findGradesByGradedTest(test);

        // uninitialised gradedTest, give everyone 0 points
        // this loop is necessary because when only some grades are found
        // then they will be corrected to 0
        for (Student student : eligible){
            if (grades.stream().noneMatch(g -> g.getOwner()==student)){
                Grade zero = new Grade();
                zero.setOwner(student);
                zero.setGradedTest(test);
                zero.setResult(0.f);
                grades.add(zero);
            }
        }

        model.addAttribute("grades",grades);
        model.addAttribute("maxPoints",test.getMaxPoints());
        return "grade_editor";
    }




}
