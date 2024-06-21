package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Function to simulate market data for each currency pair
func simulateMarketData(pair string, ch chan float64, stopCh chan struct{}, wg *sync.WaitGroup) {
	defer wg.Done()
	var min, max float64

	switch pair {
	case "EUR/USD":
		min, max = 1.0, 1.5
	case "TWD/USD":
		min, max = 0.028, 0.04
	case "JPY/USD":
		min, max = 0.006, 0.009
	}

	for {
		select {
		case <-stopCh:
			fmt.Printf("%s market data simulation stopped\n", pair)
			return
		default:
			price := min + rand.Float64()*(max-min)
			ch <- price
			time.Sleep(1 * time.Second)
		}
	}
}

// Function to perform buy/sell operations based on market conditions
func selectPair(eurUsdCh, twdUsdCh, jpyUsdCh chan float64, stopCh chan struct{}, wg *sync.WaitGroup) {
	defer wg.Done()

	for {
		select {
		case eurUsdPrice := <-eurUsdCh:
			if eurUsdPrice > 1.20 {
				fmt.Printf("EUR/USD price is %.4f - SELL operation initiated\n", eurUsdPrice)
				time.Sleep(4 * time.Second) // Simulate confirmation delay
				fmt.Println("EUR/USD SELL operation confirmed")
			}
		case twdUsdPrice := <-twdUsdCh:
			if twdUsdPrice < 1.35 {
				fmt.Printf("TWD/USD price is %.4f - BUY operation initiated\n", twdUsdPrice)
				time.Sleep(3 * time.Second) // Simulate confirmation delay
				fmt.Println("TWD/USD BUY operation confirmed")
			}
		case jpyUsdPrice := <-jpyUsdCh:
			if jpyUsdPrice < 0.0085 {
				fmt.Printf("JPY/USD price is %.4f - BUY operation initiated\n", jpyUsdPrice)
				time.Sleep(3 * time.Second) // Simulate confirmation delay
				fmt.Println("JPY/USD BUY operation confirmed")
			}
		case <-stopCh:
			fmt.Println("Trading session ended")
			return
		}
	}
}

func main() {
	// Channels for each currency pair and stop signal
	eurUsdCh := make(chan float64)
	twdUsdCh := make(chan float64)
	jpyUsdCh := make(chan float64)
	stopCh := make(chan struct{})

	// WaitGroup for synchronization
	var wg sync.WaitGroup
	wg.Add(2) // Two goroutines: market data simulation and trading decision

	// Start simulating market data for each currency pair
	go simulateMarketData("EUR/USD", eurUsdCh, stopCh, &wg)
	go simulateMarketData("TWD/USD", twdUsdCh, stopCh, &wg)
	go simulateMarketData("JPY/USD", jpyUsdCh, stopCh, &wg)

	// Start selectPair function to handle trading decisions
	go selectPair(eurUsdCh, twdUsdCh, jpyUsdCh, stopCh, &wg)

	// Simulate a trading session for 1 minute
	time.Sleep(1 * time.Minute)

	// Signal to stop market data simulation and trading decisions
	close(stopCh)

	// Wait for goroutines to finish
	wg.Wait()

	fmt.Println("All goroutines finished. Program exiting.")
}
