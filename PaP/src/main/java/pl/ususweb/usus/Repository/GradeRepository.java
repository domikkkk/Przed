package pl.ususweb.usus.Repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.ususweb.usus.entity.Grade;
import pl.ususweb.usus.entity.GradedTest;
import pl.ususweb.usus.entity.Student;

import java.util.List;

public interface GradeRepository extends JpaRepository<Grade, Integer> {

    List<Grade> findByGradedTest(GradedTest gradedTest);

    Grade findFirstByGradedTestAndOwner(GradedTest t, Student s);
}