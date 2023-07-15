package pl.ususweb.usus.Repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.ususweb.usus.entity.Student;


// This will be AUTO IMPLEMENTED by Spring into a Bean called userRepository
// CRUD refers Create, Read, Update, Delete
public interface StudentRepository extends JpaRepository<Student, Integer> {

    boolean existsByUsername(String name);

    Student findStudentByUsername(String name);
}