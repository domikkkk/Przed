package pl.projektpis.sklep.entity;


import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.cassandra.core.mapping.PrimaryKey;
import org.springframework.data.cassandra.core.mapping.Table;
import pl.projektpis.sklep.repository.ProductRepository;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.UUID;

@Table
@AllArgsConstructor
@NoArgsConstructor
@Getter
public class Basket {

    @Autowired
    private ProductRepository productRepository;

    //create basket for this owner
    public Basket(String owner){
        this.owner = owner;
    }

    public void addProduct(Product p){

        if (products==null) this.products = new LinkedList<>();
        products.add(p);
    }

    // don't fetch from repository by id and .remove!!!! it will be different java object
    public void removeProductById(UUID id){
        // is this possible with spring data directly? deleteProductById something
        if (this.products==null) return;
        Iterator<Product> itr = this.products.iterator();
        while(itr.hasNext()) {
            if(itr.next().getId().equals(id)) {
                itr.remove();
                break;
            }
        }
    }

    public Double getTally(){
        if (this.products==null) return 0.0;
        return products.stream().mapToDouble(Product::getCena).sum();
    }

    @PrimaryKey
    private String owner;
    // this needs to be a concrete type
    private LinkedList<Product> products;


    public void clear() {
        this.products.clear();
    }
}
