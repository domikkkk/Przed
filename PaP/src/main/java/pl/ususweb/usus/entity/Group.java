package pl.ususweb.usus.entity;

import lombok.*;

import javax.persistence.*;
import java.util.List;

@Getter
@Setter
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "study_groups")
public class Group {
    @Id
    @GeneratedValue
    private Integer id;
    @Column(nullable = false)
    private Integer groupSize;
    @Column(nullable = false)
    private String name;
    @Column(nullable = false)
    private String weekday;

    @Column(nullable = false)
    private Integer hour;

    @ManyToOne
    private Activity activity; //activity that this group belongs to

    @ManyToMany(mappedBy = "studentGroups")
    List<Student> students;

    @ManyToMany
    List<ExchangeOffer> offers;

    public String getDescription()
    {
        return "["+this.getActivity().getName()+"] \""+this.getName()+"\" "+this.getWeekday()+", godz."+this.getHour();
    }

}
