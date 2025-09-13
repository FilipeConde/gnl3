
//############################################################################//
//===========================  SAMPLE TEST FILE  =============================//
// For more info, check out readme                                            //
// Also, check for testing fundamentals                                       //
// Hail to the QAs!                                                           //
//############################################################################//

// fill with your header files
#include "./Unity-2.6.1/src/unity.h"
#include "./utils/utils.h"
#include "../get_next_line.h"
#include <fcntl.h>

#include <stdio.h>

// A sample file to be this test target
// #include "../sample.h"

void	setUp()
{
	return ;
}

void	tearDown()
{
	// remove("output.txt");
	// remove("control.txt");
	return ;
}

void	two_strings_should_be_equal(void)
{
	TEST_ASSERT_EQUAL_STRING("TEST", "TEST");
}

void	test_printf(void)
{
	char	*output;
	char	*def = "teste %s";
	char	*s = "Ops!";
	int		count = 0;

	CAPTURE_PRINT("output.txt", count, printf, def, s);
	output = read_file_to_str("output.txt");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Ops!", output, "Error!");
	free(output);
	remove("output.txt");
}
void	should_return_file_content_of_one_line(void)
{
	int		fd;
	int		count_control;
	char	*ptr_control;
	char	*ptr_output;
	char	*content = "Uma linha de conteudo";

	CAPTURE_PRINT("control.txt", count_control, printf, "%s", content);

	fd = open("control.txt", O_RDONLY);

	ptr_control = read_file_to_str("control.txt");
	ptr_output = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING_MESSAGE(ptr_control, ptr_output, "ERRO");
	// printf("%s\n", ptr_control);
	// printf("%s\n", ptr_output);
	free(ptr_control);
	free(ptr_output);
	close(fd);
}

void	should_return_file_content_of_two_lines(void)
{
	int		fd;
	int		count_control;
	char	*ptr_control;
	char	*ptr_output;
	char	*content = "retorna essa\nessa nao retorna";
	char	*expected = "retorna essa\n";

	CAPTURE_PRINT("control.txt", count_control, printf, "%s", content);

	fd = open("control.txt", O_RDONLY);

	ptr_control = read_file_to_str("control.txt");
	ptr_output = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, ptr_output, "ERRO");
	printf("%s\n", ptr_control);
	printf("%s\n", ptr_output);
	free(ptr_control);
	free(ptr_output);
	close(fd);
}
// TESTS get_nl_char
void	should_return_nl_index_3(void)
{
	char	*str = "tes\nte";
	
	TEST_ASSERT_EQUAL_INT(3, get_nl_char(str));
}
void	should_return_nl_index_0(void)
{
	char	*str = "\nteste";
	
	TEST_ASSERT_EQUAL_INT(0, get_nl_char(str));
}

int	main(void)
{
	UNITY_BEGIN();
	// RUN_TEST(should_return_file_content_of_one_line);
	// RUN_TEST(should_return_file_content_of_two_lines);
	
	// TESTS get_nl_char
	printf("\n>========> TESTS get_nl_char\n");
RUN_TEST(should_return_nl_index_3);
RUN_TEST(should_return_nl_index_0);
return UNITY_END();
}
