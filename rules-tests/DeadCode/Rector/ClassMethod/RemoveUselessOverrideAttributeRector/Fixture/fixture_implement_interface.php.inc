<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface ImplementInterfaceInterafce
{
    public function foo(): void;
}

final class ImplementInterfaceClass implements ImplementInterfaceInterafce
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    public function bar(): void
    {
        echo 'bar';
    }
}
?>
-----
<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface ImplementInterfaceInterafce
{
    public function foo(): void;
}

final class ImplementInterfaceClass implements ImplementInterfaceInterafce
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    public function bar(): void
    {
        echo 'bar';
    }
}
?>
