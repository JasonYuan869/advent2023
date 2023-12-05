import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.List;
import java.util.Arrays;
import java.util.HashSet;

public class Solution {
  /**
   * Returns the count of winning numbers in the line.
   *
   * @param cardInfo a string array of size 2 containing the winning numbers followed by the chosen numbers
   * @return the count of winning numbers for this game
   */
  static int processCard(String[] cardInfo) {
    int winCount = 0;

    Scanner sc = new Scanner(cardInfo[0]);
    HashSet<Integer> winningNumbers = new HashSet<Integer>();
    while (sc.hasNextInt()) {
      winningNumbers.add(sc.nextInt());
    }
    sc.close();

    sc = new Scanner(cardInfo[1]);
    while (sc.hasNextInt()) {
      if (winningNumbers.contains(sc.nextInt())) {
        winCount += 1;
      }
    }
    sc.close();

    return winCount;
  }

  static int part1(String[] lines) {
    int ret = 0;

    for (String line : lines) {
      String[] cardInfo = line.split(": ")[1].split(" \\| ");
      int winCount = processCard(cardInfo);
      int score = winCount-- > 0 ? 1 : 0;
      while (winCount > 0) {
        score *= 2;
        winCount--;
      }

      ret += score;
    }
    return ret;
  }


  static int part2(String[] lines) {
    int[] counts = new int[lines.length];
    Arrays.fill(counts, 1);

    for (int i = 0; i < lines.length; i++) {
      String line = lines[i];
      String[] cardInfo = line.split(": ")[1].split(" \\| ");
      int winCount = processCard(cardInfo);
      int copyCount = counts[i];
      for (int k = 1; k <= winCount; k++) {
        counts[k + i] += copyCount;
      }
    }

    int ret = 0;
    for (int c : counts) {
      ret += c;
    }

    return ret;
  }

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new FileReader(args[0]));
    String[] lines = br.lines().toArray(String[]::new);
    br.close();
    System.out.println(part1(lines));
    System.out.println(part2(lines));
  }
}
