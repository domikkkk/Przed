package pl.ususweb.usus.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.Repository.GradeRepository;
import pl.ususweb.usus.Repository.GradedTestRepository;
import pl.ususweb.usus.entity.Grade;
import pl.ususweb.usus.entity.GradedTest;
import pl.ususweb.usus.entity.Group;
import pl.ususweb.usus.entity.Student;

import java.util.ArrayList;
import java.util.List;

@Service
public class GradedTestService {
    @Autowired
    private GradedTestRepository tests;

    @Autowired
    private GradeRepository grades;
    public void saveGradedTest(GradedTest test){
        tests.save(test);
    }

    public GradedTest getGradedTest(int id){
        return tests.findById(id).orElse(null);
    }

    public List<GradedTest> getGradedTests(){
        return tests.findAll();
    }

    public RedirectView removeGradedTest(int id){
        tests.deleteById(id);
        return new RedirectView("/gradedTest/list");
    }

    // find student groups -> activity -> tests assosciated with this activity
    public List<GradedTest> findGradedTestsByStudent(Student student){
        ArrayList<GradedTest> allTests = new ArrayList<>();
        for (Group group : student.getStudentGroups()){
            allTests.addAll(group.getActivity().getTests());
        }
        return allTests;

    }

    // managing grades
    public void saveGrade(Grade grade) { grades.save(grade);}

    public Grade getGrade(int id){ return grades.findById(id).orElse(null); }

    public List<Grade> getGrades(){
        return grades.findAll();
    }

    public List<Grade> findGradesByGradedTest(GradedTest gradedTest) { return grades.findByGradedTest(gradedTest);}

    public String removeGrade(int id){
        Grade target = this.getGrade(id);
        String response = "Grade " + id + " Deleted (owner: "+target.getOwner()+", Test: "+target.getGradedTest()+")";
        grades.deleteById(id);
        return response;
    }

    public void purgeGradesForTest(GradedTest test) {
        if (findGradesByGradedTest(test)==null) return;
        for (Grade grade : findGradesByGradedTest(test)){
            if (grade.getGradedTest() == test) {
                removeGrade(grade.getId());
            }
        }
    }

    public Grade findGradeByGradedTestAndStudent(GradedTest t, Student s) { return grades.findFirstByGradedTestAndOwner(t,s);}
}
