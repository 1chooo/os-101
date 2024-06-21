package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Customer struct {
	name string
}

type Vehicle struct {
	v_type string
}

func main() {
	rand.New(rand.NewSource(time.Now().UnixNano()))

	ch := make(chan Vehicle)
	wg := sync.WaitGroup{}

	customers := []Customer{
		{"Customer 1"},
		{"Customer 2"},
		{"Customer 3"},
		{"Customer 4"},
		{"Customer 5"},
		{"Customer 6"},
		{"Customer 7"},
		{"Customer 8"},
		{"Customer 9"},
		{"Customer 10"},
	}

	for _, customer := range customers {
		go rent(customer, ch, &wg)
	}

	var rented []Vehicle

	for i := 0; i < len(customers); i++ {
		vehicle := <-ch
		rented = append(rented, vehicle)
	}

	wg.Wait()
	close(ch)

	printRentedVehicles(rented)
}

func rent(customer Customer, ch chan Vehicle, wg *sync.WaitGroup) Vehicle {
	defer wg.Done()

	vehicles := []Vehicle{
		{"Sedan"},
		{"SUV"},
		{"Station Wagon"},
	}

	randIndex := rand.Intn(len(vehicles))
	rentedVehicle := vehicles[randIndex]

	wg.Add(1)
	ch <- rentedVehicle

	fmt.Printf("%s has rented the vehicle %s\n", customer.name, rentedVehicle.v_type)

	return rentedVehicle
}

func printRentedVehicles(rented []Vehicle) {
	sedans := 0
	suvs := 0
	stationWagons := 0

	for _, vehicle := range rented {
		switch vehicle.v_type {
		case "Sedan":
			sedans++
		case "SUV":
			suvs++
		case "Station Wagon":
			stationWagons++
		}
	}

	fmt.Printf("Number of Sedans rented: %d\n", sedans)
	fmt.Printf("Number of SUVs rented: %d\n", suvs)
	fmt.Printf("Number of Station Wagons rented: %d\n", stationWagons)
}
