
import java.util.Scanner;

public class Problem1 {

    // 최대 차수
    static final int MAX_DEGREE = 100;

    // 다항식 입력
    public static int[] inputPoly(Scanner scan) {
        int[] poly = new int[MAX_DEGREE];
        System.out.print("항의 개수를 입력하세요.");
        int n = scan.nextInt();
        System.out.println("각 항의 계수와 차수를 입력하세요. (예: 계수 차수): ");
        for (int i = 0; i < n; i++) {
            int coef = scan.nextInt(); // 계수
            int degree = scan.nextInt(); // 차수
            if (degree >= 0 && degree < MAX_DEGREE) {
                poly[degree] = coef;
            } else {
                System.out.println("차수는 0 이상 99 이하만 가능합니다. ");
            }
        }
        return poly;
    }

    // 다항식 출력
    public static void printPoly(int[] poly) {
        boolean isFirst = true;
        for (int i = MAX_DEGREE - 1; i >= 0; i--) {
            if (poly[i] != 0) {
                if (!isFirst && poly[i] > 0) {
                    System.out.print("+");
                }
                switch (i) {
                    case 0 ->
                        System.out.print(poly[i]);
                    case 1 -> {
                        switch (poly[i]) {
                            case 1 ->
                                System.out.print("x");
                            case -1 ->
                                System.out.print("-x");
                            default ->
                                System.out.print(poly[i] + "x");
                        }
                    }
                    default -> {
                        switch (poly[i]) {
                            case 1 ->
                                System.out.print("x^" + i);
                            case -1 ->
                                System.out.print("-x^" + i);
                            default ->
                                System.out.print(poly[i] + "x^" + i);
                        }
                    }
                }
                isFirst = false;
            }
        }
        if (isFirst) {
            System.out.print("0");
        }
        System.out.println();
    }

    // 덧셈
    public static int[] addPoly(int[] a, int[] b) {
        int[] result = new int[MAX_DEGREE];
        for (int i = 0; i < MAX_DEGREE; i++) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    // 뺄셈
    public static int[] subPoly(int[] a, int[] b) {
        int[] result = new int[MAX_DEGREE];
        for (int i = 0; i < MAX_DEGREE; i++) {
            result[i] = a[i] - b[i];
        }
        return result;
    }

    // 곱셈
    public static int[] mulPoly(int[] a, int[] b) {
        int[] result = new int[MAX_DEGREE];
        for (int i = 0; i < MAX_DEGREE; i++) {
            for (int j = 0; j < MAX_DEGREE; j++) {
                if (i + j < MAX_DEGREE) {
                    result[i + j] += a[i] * b[j];
                }
            }
        }
        return result;
    }

    public static void main(String[] args) {
        try (Scanner scan = new Scanner(System.in);) {
            while (true) {
                System.out.println();
                System.out.print("연산을 하시겠습니까? \n(start: 1, stop: 0) : ");
                int choice = scan.nextInt();
                if (choice == 1) {
                    System.out.println("첫 번째 다항식을 입력합니다. ");
                    int[] poly1 = inputPoly(scan);
                    System.out.println("두 번째 다항식을 입력합니다. ");
                    int[] poly2 = inputPoly(scan);
                    System.out.print("연산자을 선택하십시오.(예: + or - or *) : ");
                    String operation = scan.next();
                    switch (operation) {
                        case "+" -> {
                            System.out.println("\n덧셈 결과 : ");
                            printPoly(addPoly(poly1, poly2));
                        }
                        case "-" -> {
                            System.out.println("\n뺄셈 결과 : ");
                            printPoly(subPoly(poly1, poly2));
                        }
                        case "*" -> {
                            System.out.println("\n곱셈 결과 : ");
                            printPoly(mulPoly(poly1, poly2));
                        }
                        default ->
                            System.out.println("올바른 연산자를 입력해주십시오. ");
                    }
                } else {
                    break;
                }
            }
        }
    }
}
