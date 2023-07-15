package pl.ususweb.usus.Repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.ususweb.usus.entity.GradedTest;

public interface GradedTestRepository extends JpaRepository<GradedTest, Integer> {

}