package pl.projektpis.sklep.repository;

import org.springframework.data.cassandra.repository.AllowFiltering;
import org.springframework.data.cassandra.repository.CassandraRepository;
import org.springframework.stereotype.Repository;
import pl.projektpis.sklep.entity.Product;

import java.util.LinkedList;
import java.util.Optional;
import java.util.UUID;

@Repository
public interface ProductRepository extends CassandraRepository<Product, UUID> {

    Optional<Product> findByNazwa(String name);

    @AllowFiltering
    LinkedList<Product> findByCenaBetween(Double cena_min, Double cena_max);

}
