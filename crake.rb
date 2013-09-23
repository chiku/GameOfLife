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
        exit 1 if $? != 0
      end
    end

    class Timed
      def run(name)
        puts "[#{Time.now.to_s.colorize(:yellow)}] #{name.colorize(:light_blue)}"
        `#{name}`
        exit 1 if $? != 0
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

  module CommandFactory
    class Compile
      attr_reader :source, :target, :options

      def initialize(source, target, options)
        @source  = source
        @target  = target
        @options = options
      end

      def build
        build_for_c
      end

    private
      def build_for_c
        "#{@options[:cc]} -o #{@target} -c #{@options[:cflags]} -I#{@options[:includes]} #{@source}"
      end
    end

    class Link
      attr_reader :sources, :target, :options

      def initialize(sources, target, options)
        @sources = sources
        @target  = target
        @options = options
      end

      def build
        build_for_c
      end

    private
      def build_for_c
        "#{@options[:cc]} -o #{@target} -c #{@options[:cflags]} -I#{@options[:includes]} #{@source}"
      end
    end
  end

  class Track
    DEFAULT_BUILD_OPTIONS = {
      :cc       => 'gcc',
      :cxx      => 'g++',
      :cflags   => '-O3 -Wall -Wextra',
      :cxxflags => '--std=c++11 -O3 -Wall -Wextra',
      :ar       => 'ar'
    }

    def initialize(include_directories, environment=ENV)
      environmental_build_options = {
        :cc       => environment['CC'],
        :cxx      => environment['CXX'],
        :cflags   => environment['CFLAGS'],
        :cxxflags => environment['CXXFLAGS'],
        :ar       => environment['AR'],
        :includes => include_directories,
      }.reject { |k, v| v.nil? }

      @build_options = DEFAULT_BUILD_OPTIONS.merge environmental_build_options
    end

    def and(options)
      [:cc, :cxx, :cflags, :cxxflags, :ar].each do |flag|
        @build_options[flag] = [@build_options[flag], options[flag]].compact.join(" ")
      end

      self
    end

    def compile(source_file, target_file, overrides={})
      current_options = @build_options.merge(overrides)
      FileUtils.mkdir_p(File.dirname target_file)
      command = CommandFactory::Compile.new(source_file, target_file, current_options).build
      Crake::Command.new.execute(command)
    end

    def link(source_files, target_file, overrides={})
      current_options = @build_options.merge(overrides)
      FileUtils.mkdir_p(File.dirname target_file)
      command = CommandFactory::Link.new(source_files, target_file, current_options).build
      Crake::Command.new.execute(command)
    end
  end
end
