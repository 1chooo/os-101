package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Pair struct {
	name  string
	price chan float64
}

func main() {
	wg := sync.WaitGroup{}

	pairs := []Pair{
		{"EUR/USD", make(chan float64, 1)},
		{"GBP/USD", make(chan float64, 1)},
		{"JPY/USD", make(chan float64, 1)},
	}

	wg.Add(2) // 增加 WaitGroup 的計數器，表示要等待兩個 goroutine 完成

	go simulateMarketData(&pairs, &wg)
	go selectPair(&pairs, &wg)

	wg.Wait() // 等待所有 goroutine 完成
}

func selectPair(pairs *[]Pair, wg *sync.WaitGroup) {
	defer wg.Done()
	for {

		select {
		case price := <-(*pairs)[0].price:
			if price > 1.2 {
				formattedPrice := fmt.Sprintf("%.5f", price)
				println(time.Now().Format("2006/01/02 15:04:05 (-0700)"), "EUR/USD:", formattedPrice, "- Buying...")
				time.Sleep(4 * time.Second)
				println(time.Now().Format("2006/01/02 15:04:05 (-0700)"), "EUR/USD", "- Bought!")
			}
		case price := <-(*pairs)[1].price:
			if price < 1.35 {
				formattedPrice := fmt.Sprintf("%.5f", price)
				println(time.Now().Format("2006/01/02 15:04:05 (-0700)"), "GBP/USD:", formattedPrice, "- Buying...")
				time.Sleep(3 * time.Second)
				println(time.Now().Format("2006/01/02 15:04:05 (-0700)"), "GBP/USD", "- Bought!")
			}
		case price := <-(*pairs)[2].price:
			if price < 0.0085 {
				formattedPrice := fmt.Sprintf("%.5f", price)
				println(time.Now().Format("2006/01/02 15:04:05 (-0700)"), "JPY/USD:", formattedPrice, "- Buying...")
				time.Sleep(3 * time.Second)
				println(time.Now().Format("2006/01/02 15:04:05 (-0700)"), "JPY/USD", "- Bought!")
			}

		default:
		}

		time.Sleep(500 * time.Millisecond)
	}
}

func simulateMarketData(pairs *[]Pair, wg *sync.WaitGroup) {
	defer wg.Done() // 減少 WaitGroup 的計數器，表示該 goroutine 已完成

	for {
		randPrice := rand.Float64()

		eur_price := randPrice*0.5 + 1.0
		gbp_price := randPrice*0.5 + 1.0

		// 嘗試往通道裡發送數據，但不會阻塞
		select {
		case (*pairs)[0].price <- eur_price:
		default:
		}

		select {
		case (*pairs)[1].price <- gbp_price:
		default:
		}

		jpy_price := randPrice*0.003 + 0.006

		// 嘗試往通道裡發送數據，但不會阻塞
		select {
		case (*pairs)[2].price <- jpy_price:
		default:
		}

		time.Sleep(1 * time.Second)
	}
}
