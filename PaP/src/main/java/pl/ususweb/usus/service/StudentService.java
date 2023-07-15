package pl.ususweb.usus.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import pl.ususweb.usus.Repository.StudentRepository;
import pl.ususweb.usus.entity.Group;
import pl.ususweb.usus.entity.Student;

import java.util.ArrayList;
import java.util.List;
import org.springframework.util.Assert;

@Service
public class StudentService {
    @Autowired
    private StudentRepository studentRepository;
    public void saveStudent(Student student){
        studentRepository.save(student);
    }

    public Student getStudent(int id){
        return studentRepository.findById(id).orElse(null);
    }

    public List<Student> getStudents(){
        return studentRepository.findAll();
    }

    public void removeStudent(int id) {
        studentRepository.deleteById(id);
    }
    public void updateStudent(Student student) {
        studentRepository.save(student);
    }

    public void addGroup(Student student, Group group) {
        student.getStudentGroups().add(group);
        studentRepository.save(student);
    }

    public void removeGroup(Student student, Group toremove){
        List<Group> groupList = student.getStudentGroups();
        Assert.isTrue(groupList.remove(toremove), "Nie posiadasz takiej grupy:"+toremove.getDescription());
        student.setStudentGroups(groupList);
        studentRepository.save(student);
    }


    public boolean checkIfUsernameExists(String name) {
        return studentRepository.existsByUsername(name);
    }

    public Student getStudentByUsername(String name) {
        return studentRepository.findStudentByUsername(name);
    }
}
