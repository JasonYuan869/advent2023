//> using toolkit latest

import scala.collection.mutable.TreeMap;
import scala.collection.mutable.HashSet

def processLines(lines: Iterator[String]): (Seq[Long], Seq[TreeMap[Long, (Long, Long)]]) = {
  // Process seed numbers
  val seedNumbers = lines.next().split(' ').drop(1).map(_.toLong)
  lines.drop(1)

  // Syntax: destination range start, source range start, range length
  val maps = Seq(
      TreeMap[Long, (Long, Long)](),
      TreeMap[Long, (Long, Long)](),
      TreeMap[Long, (Long, Long)](),
      TreeMap[Long, (Long, Long)](),
      TreeMap[Long, (Long, Long)](),
      TreeMap[Long, (Long, Long)](),
      TreeMap[Long, (Long, Long)](),
    )

  for (map <- maps) {
    lines.drop(1)
    lines.takeWhile(!_.isBlank()).foreach((i) => {
      val numbers = i.split(' ').map(_.toLong)
      map.addOne((numbers(1), (numbers(0), numbers(2))))
    })
  }

  (seedNumbers.toIndexedSeq, maps)
}

def part1(lines: Seq[String]): Long = {
  val (seedNumbers, maps) = processLines(lines.iterator)
  seedNumbers.map((n) => {
    var l = n;
    for (map <- maps) {
      map.maxBefore(l+1) match
        case Some(src, (dst, len)) => {
          if (l - src < len) {
            l = dst + (l - src)
          }
        }
        case None => {}
    }
    l
  }).min
}

def part2(lines: Seq[String]): Long = {
  val (seedNumbers, maps) = processLines(lines.iterator)
  var seedRanges = TreeMap[Long, Long]()
  for (i <- 0 to seedNumbers.length if i % 2 == 1) {
    seedRanges.addOne((seedNumbers(i-1), seedNumbers(i)))
  }

  val reverseMaps = maps.map((map) => {
    val reverseMap = TreeMap[Long, (Long, Long)]()
    map.foreach((item) => {
      val (src, (dst, len)) = item
      reverseMap.addOne((dst, (src, len)))
    })
    reverseMap
  }).reverse

  var turningPoints: HashSet[Long] = HashSet[Long]()

  reverseMaps.foreach((map) => {
    var mappedTurningPoints = HashSet[Long]()
    turningPoints.foreach((p) => {
      map.maxBefore(p+1) match
        case Some(dst, (src, len)) => {
          if (p - dst < len) {
            mappedTurningPoints.add(src + (p - dst))
          } else {
            mappedTurningPoints.add(p)
          }
        }
        case None => mappedTurningPoints.add(p)
    })
    turningPoints = mappedTurningPoints
    map.foreach((item) => {
      val (dst, (src, len)) = item
      turningPoints += src
      turningPoints += src + len - 1
    })
  })

  // Only search turning turningPoints
  turningPoints.iterator.map((point) => {
    seedRanges.maxBefore(point+1) match
      case Some(seedStart, seedRange) => {
        if (point - seedStart < seedRange) {
          var l = point;
          for (map <- maps) {
            map.maxBefore(l+1) match
              case Some(src, (dst, len)) => {
                if (l - src < len) {
                  l = dst + (l - src)
                }
              }
              case None => {}
          }
          l
        } else {
          Long.MaxValue
        }
      }
      case None => { Long.MaxValue }
  }).min
}

@main def main(path: String): Unit = {
  val lines: Seq[String] = os.read.lines(os.pwd / path)
  println(part1(lines))
  println(part2(lines))
}
