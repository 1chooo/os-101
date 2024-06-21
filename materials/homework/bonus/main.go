package main

import (
	"fmt"
	"io"
	"os"
	"sort"
)

func getPrevDir(dir string) string {
	sepa := string(os.PathSeparator)
	var fl bool = true
	for fl {
		dir = dir[:len(dir)-1]
		if string(dir[len(dir)-1]) == sepa {
			fl = false
		}
	}
	return dir[:len(dir)-1]
}

func appendFiles(file map[int]fileInfoStruct, filesInPath []string, level int) map[int]fileInfoStruct {
	var reArrangeFilesInPath []string
	for ind := range filesInPath {
		reArrangeFilesInPath = append(reArrangeFilesInPath, filesInPath[len(filesInPath)-1-ind])
	}
	sort.Sort(sort.Reverse(sort.StringSlice(reArrangeFilesInPath)))
	for _, val := range reArrangeFilesInPath { //Засовываем файлы и уровень в структуру
		file[len(file)] = fileInfoStruct{name: val, level: level}
	}

	return file
}

type mapa struct {
	tabOrNoTab int
	level      int
}

type fileInfo struct {
	name  string
	level int
}

// File information
type fileInfoStruct struct {
	name  string
	level int
}

func getGraphic(file map[int]fileInfoStruct) string {
	var out string
	var numberOfLeftLevels int

	for _, f := range file {
		if f.level == file[len(file)-1].level {
			numberOfLeftLevels++
		}
	}
	if numberOfLeftLevels > 1 {
		out = "├"
	} else {
		out = "└"
	}
	return out
}

func unique(intSlice []int) []int {
	keys := make(map[int]bool)
	list := []int{}
	for _, entry := range intSlice {
		if _, value := keys[entry]; !value {
			keys[entry] = true
			list = append(list, entry)
		}
	}
	return list
}

func elemIsInList(intSlice []int, item int) bool {
	for _, val := range intSlice {
		if val == item {
			return true
		}
	}
	return false
}

// add indentation based on the file level
func indent(file map[int]fileInfoStruct) string {
	var (
		sepa string = "│	"
		out  string
		slc  = []int{}
		slc2 = []int{}
	)
	for _, val := range file {
		slc = append(slc, val.level)
	}
	slc = unique(slc)
	for ind := 1; ind <= file[len(file)-1].level; ind++ {
		slc2 = append(slc2, ind-1)
	}
	for ind := range slc2 {
		if !elemIsInList(slc, slc2[ind]) {
			slc2[ind] = -slc2[ind]
		} else {
			continue
		}
	}
	for ind := range slc2 {
		if slc2[ind] > 0 {
			out += sepa
		} else if slc2[ind] < 0 {
			out += "	"
		} else if slc2[ind] == 0 {
			continue
		}
	}
	return out
}

func remove(slice []string, s int) []string {
	if len(slice) == 1 {
		return []string{}
	}
	return append(slice[:s], slice[s+1:]...)
}

func dirTree(out io.Writer, path string, flag bool) error {
	flag = !flag
	fileInfo := make(map[int]fileInfoStruct)
	var outString string = ""
	var level int = 0 // Subdirectory level

	// INTRODUCTORY PART
	pathToWD, _ := os.Getwd()
	pathToInitialState := pathToWD + string(os.PathSeparator) + path
	fmt.Println("Opening path:", pathToInitialState)
	openedPath, err := os.Open(pathToInitialState) // создаем путь для открытия
	if err != nil {
		panic("\nOpening failed")
	}
	// fmt.Println(pathToInitialState)
	filesInPath, err := openedPath.Readdirnames(0)
	if err != nil {
		panic("getting files names failed\n")
	}

	level += 1
	if flag {

		// fmt.Println("!flag = ", !flag)
		var filesInPath2 []string
		for ind, val := range filesInPath {
			file := pathToInitialState + string(os.PathSeparator) + filesInPath[ind]
			fileStat, err := os.Lstat(file)
			if err != nil {
				panic("Something wrong with file in approving flag")
			}
			if fileStat.IsDir() {
				// fmt.Println("IsDir")
				filesInPath2 = append(filesInPath2, val)
			}
		}
		filesInPath = filesInPath2
	}
	fileInfo = appendFiles(fileInfo, filesInPath, level)

	////////////////////////////////////////////////////////////////////////////

	for len(fileInfo) > 0 {
		for fileInfo[len(fileInfo)-1].level != level {
			level -= 1
			pathToInitialState = getPrevDir(pathToInitialState)
		}

		file := pathToInitialState + string(os.PathSeparator) + fileInfo[len(fileInfo)-1].name
		fileStat, err := os.Lstat(file)
		if err != nil {
			panic(err)
		}
		if fileStat.IsDir() {
			pathToInitialState += string(os.PathSeparator) + fileInfo[len(fileInfo)-1].name
			outString += indent(fileInfo) + getGraphic(fileInfo) + "───" + fileInfo[len(fileInfo)-1].name + "\n"
			delete(fileInfo, len(fileInfo)-1)
			openedPath, _ = os.Open(pathToInitialState)
			filesInPath, err = openedPath.Readdirnames(0)
			if err != nil {
				panic("getting files name failed\n")
			}
			level += 1
			if flag {
				var filesInPathLocal []string
				for _, val := range filesInPath {
					file := pathToInitialState + string(os.PathSeparator) + val
					fileStat, err := os.Lstat(file)
					if err != nil {
						panic(err)
					}
					if fileStat.IsDir() {
						filesInPathLocal = append(filesInPathLocal, val)
					}
				}
				filesInPath = filesInPathLocal
			}
			fileInfo = appendFiles(fileInfo, filesInPath, level)
		} else {
			var sizeOfFile int64
			var size string
			file := pathToInitialState + string(os.PathSeparator) + fileInfo[len(fileInfo)-1].name
			fileStat, _ := os.Lstat(file)
			sizeOfFile = fileStat.Size()
			if sizeOfFile == 0 {
				size = ("empty")
			} else {
				size = fmt.Sprintf("%db", sizeOfFile)
			}
			outString += fmt.Sprintf("%s%s───%s (%s)%s", indent(fileInfo), getGraphic(fileInfo), fileInfo[len(fileInfo)-1].name, size, "\n")
			delete(fileInfo, len(fileInfo)-1)
		}
	}
	out.Write([]byte(outString))
	return nil
}

func main() {
	out := os.Stdout
	if !(len(os.Args) == 2 || len(os.Args) == 3) {
		panic("usage go run main.go . [-f]")
	}
	pathToInitialState := os.Args[1] + string(os.PathSeparator) + "testdata"
	printFiles := len(os.Args) == 3 && os.Args[2] == "-f"
	err := dirTree(out, pathToInitialState, printFiles)
	if err != nil {
		panic(err.Error())
	}
}
