package pl.ususweb.usus.Repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.ususweb.usus.entity.Activity;

public interface ActivityRepository extends JpaRepository<Activity, Integer> {

}