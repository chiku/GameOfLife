require 'colorize'

module Crake
  class Command
    class Quiet
      def run(name)
        `#{name}`
      end
    end

    class Noop
      def run(name)
        puts name.colorize(:light_blue)
      end
    end

    class Verbose
      def run(name)
        puts name.colorize(:light_blue)
        `#{name}`
      end
    end

    class Timed
      def run(name)
        puts "[#{Time.now.to_s.colorize(:yellow)}] #{name.colorize(:light_blue)}"
        `#{name}`
      end
    end

    attr_accessor :runner

    def initialize
      @runner ||= Timed.new
    end

    def execute(command)
      runner.run(command)
    end
  end

  class Track
    def initialize(include_directories, environment=ENV)
      @environmental_options = {
        :cc       => environment['CC'],
        :cxx      => environment['CXX'],
        :cflags   => environment['CFLAGS'],
        :cxxflags => environment['CXXFLAGS'],
        :ar       => environment['AR']
      }

      @default_options = {
        :cc       => 'gcc',
        :cxx      => 'g++',
        :cflags   => '-O3 -Wall -Wextra',
        :cxxflags => '--std=c++11 -O3 -Wall -Wextra',
        :ar       => 'ar'
      }

      @default_options = @environmental_options.merge(@default_options)
      @include_directories = include_directories
    end

    def compile(source_file, target_file, overrides={})
      @current_options = @default_options.merge(overrides)
      FileUtils.mkdir_p(File.dirname target_file)
      command = "#{@current_options[:cc]} -o #{target_file} -c #{@current_options[:cflags]} -I#{@include_directories} #{source_file}"
      Crake::Command.new.execute(command)
    end
  end
end
