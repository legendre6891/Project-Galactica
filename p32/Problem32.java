import java.util.Arrays;

public class Problem32
{

	public static void main (String args [])
	{

		int [] solutions = new int [20];
		int solutionIndex = 0;

		int product;
		int sum = 0;
		int t1;

		for (int loop = 1; loop < 9; loop++)
			for (int loop2 = 1234; loop2 < 9877; loop2++)
				if (isValid (t1 = loop2 * 10 + loop))
					if ((product = loop * loop2) < 10000 && isValid (product * 100000 + t1))
						solutions [solutionIndex++] = product;

		for (int loop = 12; loop < 99; loop++)
			for (int loop2 = 123; loop2 < 988; loop2++)
				if (isValid (t1 = loop2 * 100 + loop))
					if ((product = loop * loop2) < 10000 && isValid (product * 100000 + t1))
						solutions [solutionIndex++] = product;

		int [] finalSolutions = new int [solutionIndex];
		System.arraycopy (solutions, 0, finalSolutions, 0, solutionIndex);

		Arrays.sort (finalSolutions);

		for (int index = 0; index < finalSolutions.length; index++)
			if (index > 0 && finalSolutions [index] == finalSolutions [index - 1])
				continue;
			else
				sum += finalSolutions [index];

		System.out.println ("Sum of solutions: " + sum);

	}

	private static boolean isValid (int num)
	{

		String numStr = String.valueOf (num);

		if (numStr.indexOf ('0') != -1)
			return false;

		boolean valid = true;

		for (int index = 0; valid && index < numStr.length () - 1; index++)
			if (numStr.indexOf (numStr.charAt (index), index + 1) != -1)
				valid = false;

		return valid;

	}

}
